
import cv2

from logic.DatabaseController import *

class RecognitionController( QWidget ):
    """
        Controls recognition process e.g choosing algorithm, calling algorithm, training process.
        TODO : Not tested yet.
    """
    def __train_algorithm(self):
        print("Training recognition algorithms")
        #Do select
        #Train, label is identifer

        allImg = self.dbCtl.selectImages()
        trainImg = []
        trainOwner = []
        for elem in allImg:
            print("Adding {}".format(elem))
            trainImg.append(elem[0])
            trainOwner.append(elem[1])

        self.LBPH.train(trainImg,trainOwner)
        print("Training is done")

    def __init__(self, parent = None):
        QWidget.__init__(self, parent = None)
        self.LBPH = cv2.face.LBPHFaceRecongnizer_create()
        self.Eigen = cv2.createEigenFaceRecognizer()
        self.Fisher = cv2.createFisherFaceRecognizer()
        self.dbCtl = DatabaseController()
        self.current_recognizer = self.LBPH
        self.__train_algorithms()

    def recongnizeImage(self, image):
        """
            :param image: Input image of face to recognize.
            :return: If some image is recognized, tuple of type (name, last_name, gender, precision) is returned,
                if image is not found, None is returned
            TODO : Not tested yet
        """
        return self.LBPH.predict(image)



