from PyQt5.QtWidgets import *
from PyQt5 import QtGui

__COMMON_FONT_SIZE__ = 20

class FoundFacesLabel( QLabel ):
    def __init__(self, string: str):
        QLabel.__init__(self, string)
        self.setFont(QtGui.QFont("Arial", __COMMON_FONT_SIZE__))