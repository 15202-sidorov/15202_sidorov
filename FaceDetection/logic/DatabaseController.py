from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5 import QtSql

import cv2
import sqlite3
import os
import numpy

import sys

class DatabaseController( QWidget ):
    """
        Controls SQLITE database interface.
        TODO: image_data blob in image table should contain not the whole image, but face.
    """
    __DATABASE_TYPE__ = "QSQLITE"
    __DATABASE_NAME__ = "logic\\FaceDatabase"
    __PERSON_TABLE_NAME__ = "person"
    __IMAGE_TABLE_NAME__ = "image"

    __DB_IMAGE_DATA_INDEX__ = 1
    __DB_IMAGE_OWNER_ID_INDEX__ = 2

    IMAGE_DATA_INDEX = 0
    IMAGE_OWNER_INDEX = 1

    def __initializeModel__(self):
        self.model = QtSql.QSqlTableModel()
        self.model.setTable(self.__PERSON_TABLE_NAME__)
        self.model.setEditStrategy(QtSql.QSqlTableModel.OnFieldChange)
        self.model.select()
        self.model.setHeaderData(0, Qt.Horizontal, "ID")
        self.model.setHeaderData(1, Qt.Horizontal, "First name")
        self.model.setHeaderData(2, Qt.Horizontal, "Last name")
        self.model.setHeaderData(3,Qt.Horizontal, "Gender")

    def __createView__(self, title: str):
        self.view = QTableView()
        self.view.setModel(self.model)
        self.view.setWindowTitle(title)

    def __init__(self, parent = None):
        QWidget.__init__(self, parent = None)
        self.db = QtSql.QSqlDatabase.addDatabase(self.__DATABASE_TYPE__)
        self.db.setDatabaseName(self.__DATABASE_NAME__)

        if not self.db.open():
            print("Could not open database")
            print(self.db.lastError().text())
            return

        self.sqlitedb = sqlite3.connect("FaceDatabase")
        self.cursor = self.sqlitedb.cursor()

        self.__initializeModel__()
        self.__createView__("Imported Faces")
        layout = QVBoxLayout()
        layout.addWidget(self.view)
        self.setLayout(layout)
        self.setWindowTitle("All faces")
        self.setMinimumSize(self.view.width(), self.view.height())

    def insertPerson(self, name: str, last_name: str, gender: str):
        query = QtSql.QSqlQuery(self.db)
        action = "INSERT INTO " + self.__PERSON_TABLE_NAME__ + " (person_name, person_last_name, person_gender) "+ \
                  "VALUES (:name, :last_name, :gender)"
        query.prepare(action)
        query.bindValue(":name", name)
        query.bindValue(":last_name", last_name)
        query.bindValue(":gender", gender)

        if ( not query.exec_() ):
            print(query.lastError().text())
            print(query.boundValues())
            print("Executed query : " + query.executedQuery())

        self.__init__(self)

    def insertImage(self, data, owner_id : int):
        """
        :param data: Any type of data is supported. Represents actual RGB image data.
        :param attributes: Attributes used for image comparison (Neural network, for example)
        :param owner_id: Owner(the one who is on the photo) of this image

        """

        action = "INSERT INTO " + self.__IMAGE_TABLE_NAME__ + " (image_data, image_owner_id) VALUES" + \
                 ' (?, ?);'
        self.sqlitedb.execute(action, (bytes(data), owner_id))
        self.sqlitedb.commit()

    def selectImages(self):
        """
        :return: Array of images in database  and its attributes(encoding)

        """

        result = []
        action = "SELECT * FROM " + self.__IMAGE_TABLE_NAME__
        self.cursor.execute(action)
        while( True ):
            result_ = self.cursor.fetchone()
            if ( None == result_ ):
                break

            result.append((cv2.imdecode(numpy.asarray(bytearray(result_[self.__DB_IMAGE_DATA_INDEX__])),1),
                           result_[self.__DB_IMAGE_OWNER_ID_INDEX__]))
        return result

def insertImagesFromDirectory(dbCtl : DatabaseController):
    """
        Run this script, in order to insert all images from image directory, if needed.
    :param dbCtl: database controller, which is bound to a database.
    :return: None
    """
    directory = "..\\images"
    i = 0
    for file in os.listdir(directory):
        filename = os.fsdecode(file)
        if filename.endswith(".pgm"):
            with open(directory + "\\" + filename, 'rb') as content_file:
                content = content_file.read()
                i += 1
                dbCtl.insertImage(content, i)

def seeDatabase():
    app = QApplication(sys.argv)
    dbCtl = DatabaseController()
    dbCtl.show()
    sys.exit(app.exec_())