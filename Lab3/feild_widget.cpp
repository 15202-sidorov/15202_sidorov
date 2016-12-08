#include "feild_widget.h"

FeildWidget::FeildWidget(   QWidget *parent, 
                            int length_, 
                            int height_,
                            std::vector<int> alive_cells) 
	: QWidget(parent)
{
	feild = new Feild(length_,height_);
	setFixedSize(parent->width() - step_from_parent_x, 
                 parent->height()- step_from_parent_y);
    dx_cell = (this->width())/(feild->getWidth()) + 1;
    dy_cell = (this->height())/(feild->getHeight()) + 1 ;
    if ((dx_cell == 0) || (dy_cell == 0))
    {
        throw -1;
    }

    time = new QTimer(this);

    for (int i = 0; i < alive_cells.size()-1; i+=2)
    {
        feild->changeCellState(alive_cells[i],alive_cells[i+1]);
    }


    connect(time,SIGNAL(timeout()),this,SLOT(StepOnce()));

};

void FeildWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    //painter.setPen(Qt::black);
    painter.setBrush(Qt::black);

    painter.drawRoundedRect(0,0,this->width()-1,this->height()-1,3,3);

   // DrawGrid(&painter);
    DrawCells(&painter);
}

inline void FeildWidget::DrawGrid(QPainter *painter)
{

    for (int i = 0; i < this->width(); i += dx_cell)
    {
        if (this->width() - i < dx_cell)
        {
            break;
        }
        painter->drawLine(i,0,i,this->height());
    }

    for (int i = 0; i < this->height(); i += dy_cell)
    {
        if (this->height()- i < dy_cell) 
        {
            break;
        }
        painter->drawLine(0,i,this->width(),i);
    }
}

inline void FeildWidget::DrawCells(QPainter *painter)
{
    painter->setBrush(Qt::white);

    for (int i = 0; i < this->width(); i += dx_cell)
    {
        for (int j = 0; j < this->height(); j += dy_cell)
        {

            if (feild->getCellState(i/(dx_cell),j/(dy_cell)))
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