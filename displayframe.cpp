#include "displayframe.h"
#include <QPainter>
DisplayFrame::DisplayFrame(QWidget *parent):QFrame(parent)
{

}

void DisplayFrame::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->geometry(),Qt::white);
}
