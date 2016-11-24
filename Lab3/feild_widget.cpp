#include "feild_widget.h"


void FeildWidget::paintEvent(QPaintEvent *)
{
	
	QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setPen(Qt::black);
    painter.drawRoundedRect(0,0,this->width()-1,this->height()-1,3,3);

    int dx = this->width()/feild->getWidth();
    int dy = this->height()/feild->getHeight();

    //drawing grid
    for (int i = 0; i < this->width(); i += dx)
    {
 		if (this->width() - i < dx)
 		{
 			break;
 		}
 		painter.drawLine(i,2,i,this->height());
    }

    for (int i = 0; i < this->height(); i += dy)
    {
 		if (this->height() - i < dy) 
 		{
 			break;
 		}
 		painter.drawLine(2,i,this->width(),i);
    }

}