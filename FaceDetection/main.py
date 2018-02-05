from ui.FoundFacesLabel import *
from ui.FoundFacesDisplay import *
from ui.AlgorithmDisplay import *
from ui.CameraDisplay import *
from ui.ChooseFileDialog import *
from ui.MainWindow import *

from logic.AnalizeController import *
from logic.HistogramController import *
from logic.DatabaseController import *

def main():

    app = QApplication(sys.argv)

    windowWidget = MainWindow()
    windowWidget.resize(1500,800)
    windowWidget.setWindowTitle("FaceDetector")

    left_layout = QVBoxLayout()
    right_layout = QVBoxLayout()
    data_layout = QVBoxLayout()
    recognition_layout = QHBoxLayout()
    main_layout = QHBoxLayout()

    #Initialize left layout

    algDisplay = AlgorithmsDisplay(windowWidget)
    camera = CameraDisplay(windowWidget)
    enter_file_name_button = QPushButton("Choose image")
    open_database_button = QPushButton("See database")
    enter_file_name_button.setFixedSize(camera.width(), 50)
    open_database_button.setFixedSize(int(camera.width()/2 - 30), 100)
    file_dialog = ChooseFileDialog(windowWidget)
    faces_display = FoundFacesDisplay(windowWidget)

    analizator = AnaliseController()
    graphicsCtl = HistogramContoller()
    dbCtl = DatabaseController()

    analizator.moveToThread(windowWidget.workingThread)
    graphicsCtl.moveToThread(windowWidget.workingThread)
    dbCtl.moveToThread(windowWidget.workingThread)

    camera.doubleClicked.connect(graphicsCtl.showHistogram)
    enter_file_name_button.clicked.connect(file_dialog.getFilesSlot)
    open_database_button.clicked.connect(dbCtl.show)

    analizator.hog.imageAnalised.connect(camera.processCapture)
    analizator.hog.newFaces.connect(faces_display.processFaces)
    analizator.hog.gotTime.connect(graphicsCtl.newValue)
    analizator.viola.imageAnalised.connect(camera.processCapture)
    analizator.viola.newFaces.connect(faces_display.processFaces)
    analizator.viola.gotTime.connect(graphicsCtl.newValue)

    file_dialog.fileFound.connect(analizator.fileFoundSlot)
    algDisplay.chosen.connect(analizator.changeAlgorithm)

    left_layout.addWidget(enter_file_name_button)
    left_layout.addWidget(camera)
    left_layout.addWidget(algDisplay)

    #Initialize right layout

    right_layout.addWidget( FoundFacesLabel("Faces found:") )
    right_layout.addWidget( faces_display )

    data_layout.addWidget( FoundFacesLabel("Name : Erica"))
    data_layout.addWidget( FoundFacesLabel("Last Name : Albright"))
    data_layout.addWidget( FoundFacesLabel("Sex : Female"))
    data_layout.addWidget( FoundFacesLabel("Precision: 94%"))
    recognition_layout.addLayout(data_layout)
    recognition_layout.addWidget(open_database_button)
    right_layout.addLayout(recognition_layout)

    main_layout.addLayout(left_layout)
    main_layout.addLayout(right_layout)
    windowWidget.setLayout(main_layout)
    windowWidget.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()