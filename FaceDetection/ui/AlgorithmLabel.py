from PyQt5.QtWidgets import *
from PyQt5 import QtGui
from PyQt5.QtCore import *

__COMMON_FONT_SIZE__ = 20

class AlgorithmLabel( QLabel ):
    """
        UI label that represents chosen algorithm.
        Highlighted in red on mouse over.
    """
    chosen = pyqtSignal(int)

    def __init__(self, string):
        QLabel.__init__(self, string)
        self.setMouseTracking(True)
        self.setFont( QtGui.QFont("Arial",__COMMON_FONT_SIZE__) )
        self.algNo = 0

    def enterEvent(self, event):
        self.setStyleSheet(' color : red ')

    def leaveEvent(self, event):
        self.setStyleSheet(' color : black ')

    def mouseReleaseEvent(self, ev: QtGui.QMouseEvent):
        self.chosen.emit(self.algNo)