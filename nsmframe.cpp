#include "nsmframe.h"
#include <QPainter>
NSMFrame::NSMFrame(QWidget *parent):mParent(parent)
{
    refresh=false;
    setMouseTracking(true);
}

void NSMFrame::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rect=this->rect();
    painter.setViewport(0,0,rect.width()/2,rect.height());
    painter.setWindow(0,0,rect.width()/2,rect.height());
    drawDemandAndArcFlows(&painter);
    painter.setViewport(rect.width()/2,0,rect.width()/2,rect.height());
    drawCostAndDualVariables(&painter);
}
void NSMFrame::drawDemandAndArcFlows(QPainter* painter){

}
void NSMFrame::drawCostAndDualVariables(QPainter* painter){

}
void NSMFrame::mousePressEvent(QMouseEvent *event)
{

}

void NSMFrame::mouseMoveEvent(QMouseEvent *event)
{

}

void NSMFrame::mouseReleaseEvent(QMouseEvent *event)
{

}

void NSMFrame::wheelEvent(QWheelEvent *event)
{

}

void NSMFrame::keyPressEvent(QKeyEvent *event)
{

}

void NSMFrame::keyReleaseEvent(QKeyEvent *event)
{

}
