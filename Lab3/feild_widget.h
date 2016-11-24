#ifndef _FEILD_WIDGET_H_
#define _FEILD_WIDGET_H_

#include <QtGui>
#include "feild.h"
	
class FeildWidget: public QWidget
{
	Q_OBJECT
public:	
	FeildWidget(QWidget *parent, int length_, int height_) 
		: QWidget(parent)
	{
		feild = new Feild(length_,height_);
		setFixedSize(parent->width()-60, parent->height()-160);
	};
	void paintEvent(QPaintEvent *);
	
	~FeildWidget()
	{
		delete feild;
	};
private:
	Feild *feild;

};

#endif
