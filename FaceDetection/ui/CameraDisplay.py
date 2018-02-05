from PyQt5.QtWidgets import *
from PyQt5 import QtGui
from PyQt5.QtCore import *
from PyQt5.QtGui import *

class CameraDisplay( QGraphicsView ):
    """
        Displays the analised image chosen for analises.
    """

    doubleClicked = pyqtSignal()

    def __init__(self, parent):
        QGraphicsView.__init__(self, parent)
        self.scene = QGraphicsScene()
        self.setScene(self.scene)
        self.setFixedSize(700, 600)

    @pyqtSlot(QImage)
    def processCapture(self, image: QImage):
        self.scene.clear()
        self.scene.addPixmap(QtGui.QPixmap.fromImage(image))
        self.scene.update()
        self.setScene(self.scene)

    def mouseDoubleClickEvent(self, event):
        self.doubleClicked.emit()
