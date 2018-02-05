from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

from ui.HOGAlgorithmLabel import *
from ui.VIOLAAlgorithmLabel import *

class AlgorithmsDisplay( QWidget ):
    """
        UI widget containing the list of all algorithms possible.
    """

    chosen = pyqtSignal(int)

    def __init__(self, parent = None):
        QWidget.__init__(self, parent = None)
        layout = QVBoxLayout()
        self.__algorithm_labels = [ HOGAlgorithmLabel("HOG"), VIOLAAlgorithmLabel("VIOLA JONES") ]

        for label in self.__algorithm_labels:
            layout.addWidget(label)
            label.chosen.connect(self.__forwardSignal)

        self.setLayout(layout)
        self.setMouseTracking(True)

    @pyqtSlot(int)
    def __forwardSignal(self, algNo: int):
        self.chosen.emit(algNo)