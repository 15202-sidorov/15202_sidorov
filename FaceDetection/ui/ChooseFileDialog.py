from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

class ChooseFileDialog( QWidget ):
    """
        UI dialog, allows user to chose picture from file system for further analises.
    """
    fileFound = pyqtSignal(str)
    def __init__(self, parent = None):
        QWidget.__init__(self, parent = None)

    def getFiles(self):
        dlg = QFileDialog()
        dlg.setFileMode(QFileDialog.AnyFile)


        if dlg.exec_():
            self.fileList = dlg.selectedFiles()
        else:
            self.fileList = [""]

    @pyqtSlot()
    def getFilesSlot(self):
        self.getFiles()
        self.fileFound.emit(self.fileList[0])