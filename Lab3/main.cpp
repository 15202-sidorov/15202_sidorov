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
	FeildWidget f(&window,10,10);
	Menu menu(&window);
	
	QVBoxLayout layout;

	

	layout.addWidget(&menu);
	layout.addWidget(&f);
	layout.setAlignment(&f,Qt::AlignHCenter);
	layout.setAlignment(&menu,Qt::AlignHCenter);
	
	window.setLayout(&layout);
	window.show();

	/*
	std::string input;
	std::getline(std::cin,input);
	QObject::connect(&button,SIGNAL(clicked()),&paint,SLOT(update()));
	paint.update();
	*/
	/*
	QTextEdit textEdit;
	QPushButton quitButton("Quit");
 	
 	QObject::connect(&quitButton,SIGNAL(clicked()), qApp, SLOT(quit()));
 	QVBoxLayout layout;

 	layout.addWidget(&quitButton);
 	layout.addWidget(&textEdit);

 	QWidget window;
 	window.setLayout(&layout);

 	window.show();
	*/
	return app.exec();
}