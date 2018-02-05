from PyQt5.QtWidgets import *
from PyQt5 import QtGui
from PyQt5.QtCore import *
from PyQt5.QtGui import *

import copy
import cv2
import time

__FACE_PADDING__ = 20

class VIOLAAnalizator( QWidget ):
    """
        Does the same as HOGAnalizator, only using another algorithm
    """
    imageAnalised = pyqtSignal(QImage)
    newFaces = pyqtSignal(list)
    gotTime = pyqtSignal(str, int, int)
    __CLASSIFIER_NAME__ = 'logic\\1.xml'

    def __init__(self, parent = None):
        QWidget.__init__(self,parent = None)
        self.classifier = cv2.CascadeClassifier(self.__CLASSIFIER_NAME__)

    def __analiseImage(self, image):
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        start = time.time()
        faces = self.classifier.detectMultiScale(gray, 1.3, 5)
        end = time.time()
        resultedTime = end - start
        self.gotTime.emit(self.imageName, resultedTime * 1000, 1)
        images_of_faces = []
        if ( len(faces) == 0 ):
            return
        for (x, y, w, h) in faces:
            face = copy.deepcopy(image[y-__FACE_PADDING__:y+h + __FACE_PADDING__, x - __FACE_PADDING__:x+w + __FACE_PADDING__])
            rgbFace = cv2.cvtColor(face, cv2.COLOR_BGR2RGB)
            faceImage = QtGui.QImage(rgbFace, rgbFace.shape[1], rgbFace.shape[0], 3 * rgbFace.shape[1],
                                     QtGui.QImage.Format_RGB888)
            images_of_faces.append(faceImage)

        self.newFaces.emit(images_of_faces)

        for (x, y, w, h) in faces:
            cv2.rectangle(image, (x, y), (x + w, y + h), (255, 0, 0), 2)

        rgbImage = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        image = QtGui.QImage(rgbImage, rgbImage.shape[1], rgbImage.shape[0], 3 * rgbImage.shape[1],
                             QtGui.QImage.Format_RGB888)
        self.imageAnalised.emit(image)

    @pyqtSlot(str)
    def fileFoundSlot(self, imageName: str):
        self.imageName = imageName
        image = cv2.imread(imageName)
        self.__analiseImage(image)
