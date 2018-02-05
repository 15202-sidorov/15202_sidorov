from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

class MainWindow( QWidget ):
    workingThread = QThread()
    def __init__(self, parent = None):
        QWidget.__init__(self, parent = None)
        self.workingThread.start()

    def closeEvent(self, event):
        self.workingThread.stop()