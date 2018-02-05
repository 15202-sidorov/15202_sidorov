
from PyQt5 import QtGui

from logic.RecognitionController import *

import copy
import cv2
import dlib
import time

__FACE_PADDING__ = 20

class HOGAnalizator( QWidget ):
    """
        Analise the image using HOG algorithm to locate faces in picture.
        FileFoundSlot is bound to file descriptor which will emit signal when a file is selected for analise.
        AnaliseImage method does all the analise of the image and highlights the face in image if present.
    """

    imageAnalised = pyqtSignal(QImage)
    newFaces = pyqtSignal(list)
    gotTime = pyqtSignal(str, int, int)

    def __init__(self):
        QWidget.__init__(self)
        self.face_detector = dlib.get_frontal_face_detector()

    def __analiseImage(self, frame):
        start = time.time()
        detected_faces = self.face_detector(frame, 1)
        end = time.time()
        resultedTime = end - start
        self.gotTime.emit(self.imageName, resultedTime * 1000, 0)

        print("I found {} faces".format(len(detected_faces)))

        if ( len(detected_faces) == 0 ):
            return
        images_of_faces = []

        # Loop through each face we found in the image
        for i, face_rect in enumerate(detected_faces):
            #  Detected faces are returned as an object with the coordinates
            # of the top, left, right and bottom edges
            print("- Face #{} found at Left: {} Top: {} Right: {} Bottom: {}".format(i, face_rect.left(),
                                                                                    face_rect.top(),
                                                                                    face_rect.right(),
                                                                                    face_rect.bottom()))
            face = copy.deepcopy(frame[face_rect.top() - __FACE_PADDING__:face_rect.bottom() + __FACE_PADDING__, face_rect.left() - __FACE_PADDING__:face_rect.right() + __FACE_PADDING__])


            rgbFace = cv2.cvtColor(face, cv2.COLOR_BGR2RGB)
            faceImage = QtGui.QImage(rgbFace, rgbFace.shape[1], rgbFace.shape[0], 3 * rgbFace.shape[1],
                                     QtGui.QImage.Format_RGB888)
            images_of_faces.append(faceImage)

        self.newFaces.emit(images_of_faces)

        for i, face_rect in enumerate(detected_faces):
            cv2.rectangle(frame, (face_rect.left(), face_rect.top()), (face_rect.right(), face_rect.bottom()),
                          (0, 255, 0), 2)

        rgbImage = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        image = QtGui.QImage(rgbImage, rgbImage.shape[1], frame.shape[0], 3 * rgbImage.shape[1], QtGui.QImage.Format_RGB888)
        self.imageAnalised.emit(image)

    def fileFoundSlot(self, imageName: str):
        self.imageName = imageName
        image = cv2.imread(imageName)
        self.__analiseImage(image)