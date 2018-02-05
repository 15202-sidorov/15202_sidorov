from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
import matplotlib.pyplot as plt

class HistogramContoller( QWidget ):
    """
        Histogram interface. Shows time of work of all algorithms.
    """
    class AlgoProperty:
        """
            Algorithm num and color, in which time of work is represented in histogram.
        """

        def __init__(self, num: int):
            self.id = num
            if ( 0 == num ):
                self.color = 'c'
            else:
                self.color = 'r'
            self.filenames = []
            self.times = []

    def __init__(self, parent = None):
        QWidget.__init__(self, parent = None)
        self.algorithms = [self.AlgoProperty(0), self.AlgoProperty(1)]

    @pyqtSlot(str, int, int)
    def newValue(self, filename: str, time: int, algorithmNo: int):
        self.algorithms[algorithmNo].filenames.append(filename[len(filename) - 5:len(filename)])
        self.algorithms[algorithmNo].times.append(time)

    @pyqtSlot()
    def showHistogram(self):
        plt.bar(self.algorithms[0].filenames, self.algorithms[0].times, color=self.algorithms[0].color)
        plt.bar(self.algorithms[1].filenames, self.algorithms[1].times, color=self.algorithms[1].color)
        plt.show()