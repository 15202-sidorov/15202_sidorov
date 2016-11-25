//model- view - constroller

//gmake -project && qmake && make
//qmake -> makefile comes out
//make

#include <QtGui>
#include <QPainter>
#include <iostream>

#include "feild_widget.h"
#include "menu_widget.h"

int main(int argc, char **argv)
{
	QApplication app(argc,argv);
	
	QWidget window;
	window.setFixedSize(500,600);
	FeildWidget f(&window,20,20);
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

	window.setLayout(&layout);
	window.show();

	return app.exec();
}