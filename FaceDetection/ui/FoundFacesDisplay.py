from PyQt5.QtWidgets import *
from PyQt5 import QtGui
from PyQt5.QtCore import *


class FoundFacesDisplay( QGraphicsView ):
    """
        Displays found faces from chosen picture.
    """
    def __init__(self, parent):
        QGraphicsView.__init__(self, parent)
        self.scene = QGraphicsScene()
        self.setScene(self.scene)
        self.setFixedSize(700, 600)
        self.currentIndex = 0

    @pyqtSlot(list)
    def processFaces(self, images: list):
        self.images = images
        self.scene.clear()
        self.scene.addPixmap(QtGui.QPixmap.fromImage(images[0]))

    def mousePressEvent(self, event):
        self.__nextImage()

    def __nextImage(self):
        self.scene.clear()
        self.currentIndex += 1
        self.currentIndex %= len(self.images)

        self.scene.addPixmap(QtGui.QPixmap.fromImage(self.images[self.currentIndex]))