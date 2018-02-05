
//sizes of all widgets are constant

#include <QtGui>
#include <QPainter>
#include <iostream>

#include "feild_widget.h"
#include "menu_widget.h"

#include "get_feild.h"

int main(int argc, char **argv)
{
	Feild_Loader load;

	QApplication app(argc,argv);
	QWidget window;
	window.setFixedSize(500,600);

	FeildWidget f(&window,
				  load.get_height(),
				  load.get_width(),
				  load.get_cells());
	Menu menu(&window);
	QVBoxLayout layout;
	layout.addWidget(&menu);
	layout.addWidget(&f);
	layout.setAlignment(&f,Qt::AlignHCenter);
	layout.setAlignment(&menu,Qt::AlignHCenter);
	
	QObject::connect(&menu,SIGNAL(MakeStep()),&f,SLOT(StepOnce()));
	QObject::connect(&menu,SIGNAL(RunGame()),&f,SLOT(StartPlay()));
	QObject::connect(&menu,SIGNAL(StopGame()),&f,SLOT(StopPlay()));
	QObject::connect(&menu,SIGNAL(ClearFeild()),&f,SLOT(Clear()));
	QObject::connect(&menu,SIGNAL(Resize(int,int)),&f,SLOT(changeSize(int,int)));

	window.setLayout(&layout);
	window.show();

	return app.exec();
}