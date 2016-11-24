#ifndef PAINTER
#define PAINTER

#include <QtGui>

class PainterWindow: public QWidget
{
public:
	explicit PainterWindow(QWidget * parent = 0) 
		: QWidget(parent), x(100), y(100){};
	
	Q_OBJECT

signals:

public slots:
	void addCoord()
	{
		x += 50;
		y += 50;
		this->update();
	}

private:
	int x,y;
	void paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
   		painter.setPen(Qt::blue);
    	painter.setFont(QFont("Arial", 30));
    	painter.drawLine(0,0,x,y);
	}
};




#endif