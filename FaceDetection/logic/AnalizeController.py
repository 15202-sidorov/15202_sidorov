from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

from logic.HOGAnalizator import *
from logic.VIOLAAnalizator import *

class AnaliseController( QWidget ):
    """
        In charge of all detection algorithms.
        Keeps track of current detection algorithm.
        Provides signal for current algorithm to start analise a file.
    """
    def __init__(self, parent = None):
        QWidget.__init__(self, parent = None)
        self.hog = HOGAnalizator()
        self.viola = VIOLAAnalizator()
        self.currentAlgorithm = self.hog

    @pyqtSlot(int)
    def changeAlgorithm(self, algNo: int):
        """
            Change current algorithm to the algorithm with algNo.
        :param algNo: Number of new current algorithm.
        :return:
        """
        if ( 0 == algNo ):
            self.currentAlgorithm = self.hog
        else:
            self.currentAlgorithm = self.viola

    @pyqtSlot(str)
    def fileFoundSlot(self, imageName: str):
        """
            Transfers signal to current algorithm.
        :param imageName: Image path in filesystem, chosen by user.
        :return:
        """
        if ( "" == imageName ):
            return
        self.currentAlgorithm.fileFoundSlot(imageName)