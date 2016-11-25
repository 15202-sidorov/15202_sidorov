#include "feild_widget.h"

FeildWidget::FeildWidget(QWidget *parent, int length_, int height_) 
	: QWidget(parent)
{
	feild = new Feild(length_,height_);
	setFixedSize(parent->width() - step_from_parent_x, 
                 parent->height()- step_from_parent_y);
    dx_cell = this->width()/feild->getWidth();
    dy_cell = this->height()/feild->getHeight();

    time = new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(StepOnce()));

};

void FeildWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setPen(Qt::black);

    DrawGrid(&painter);
    DrawCells(&painter);
}

void FeildWidget::DrawGrid(QPainter *painter)
{
    painter->drawRoundedRect(0,0,this->width()-1,this->height()-1,3,3);

    for (int i = 0; i < this->width(); i += dx_cell)
    {
        if (this->width() - i < dx_cell)
        {
            break;
        }
        painter->drawLine(i,2,i,this->height());
    }

    for (int i = 0; i < this->height(); i += dy_cell)
    {
        if (this->height() - i < dy_cell) 
        {
            break;
        }
        painter->drawLine(2,i,this->width(),i);
    }
}

void FeildWidget::DrawCells(QPainter *painter)
{
    painter->setBrush(Qt::green);

    for (int i = 0; i < this->width(); i += dx_cell)
    {
        for (int j = 0; j < this->height(); j += dy_cell)
        {
            if ((this->width() - i < dx_cell) || (this->height() - j < dy_cell))
            {
                break;
            }
            if (feild->getCellState(i/dx_cell,j/dy_cell))
            {
                painter->drawRect(i,j,dx_cell,dy_cell);
            }
        }
    } 
}

void FeildWidget::mousePressEvent(QMouseEvent *event)
{
    if (state == PLAY)
    {
        return;
    }
    QPoint mousePos = event->pos();
    feild->changeCellState(mousePos.x()/dx_cell,
                        mousePos.y()/dy_cell);
    update();
}

void FeildWidget::StepOnce()
{
    feild->play_once();
    update();
}


void FeildWidget::Clear()
{
    feild->clear();
    update();
    return; 
}

FeildWidget::~FeildWidget()
{
    delete feild;
    delete time;
};