#include "nsmframe.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
NSMFrame::NSMFrame(QWidget *parent):mParent(parent)
{
    refresh=false;
    init();
    setMouseTracking(true);
}

void NSMFrame::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rect=this->rect();
    painter.translate(winOffsetX,winOffsetY);
    painter.scale(winScale,winScale);
    painter.setViewport(0,0,rect.width()/2,rect.height());
    painter.setWindow(0,0,rect.width()/2,rect.height());

    drawDemandAndArcFlows(&painter);
    painter.setViewport(rect.width()/2,0,rect.width()/2,rect.height());
    drawCostAndDualVariables(&painter);
}

void NSMFrame::drawDemandAndArcFlows(QPainter* painter){

    painter->drawLine(0,0,100,100);
}

void NSMFrame::drawCostAndDualVariables(QPainter* painter){
 painter->drawLine(0,0,100,100);
}
void NSMFrame::mousePressEvent(QMouseEvent *event)
{
    int x=event->x();
    int y=event->y();
    if(event->button()==Qt::RightButton){
        winStartMove=true;
        moveVertexPos=0;
        maybeMultiSelect=false;
        readyMultiMove=false;
        createEdge=false;
        findEdgeTail=false;
        winOffsetX=winOriOffsetX;
        winOffsetY=winOriOffsetY;
        winStartOffsetX=x;
        winStartOffsetY=y;
        setCursor(Qt::OpenHandCursor);
    }
    update();
    event->accept();
}

void NSMFrame::mouseMoveEvent(QMouseEvent *event)
{
    setFocus();
    int x=event->x();
    int y=event->y();
    if(winStartMove){
        winOffsetX=winOriOffsetX+(event->x()-winStartOffsetX);
        winOffsetY=winOriOffsetY+(event->y()-winStartOffsetY);
    }
    update();
    event->accept();
}

void NSMFrame::mouseReleaseEvent(QMouseEvent *event)
{
    int x=event->x();
    int y=event->y();

    if(event->button()==Qt::RightButton){
        winStartMove=false;
        winOriOffsetX=winOffsetX;
        winOriOffsetY=winOffsetY;
        setCursor(Qt::ArrowCursor);
    }
    moveVertexPos=0;
    maybeMultiSelect=false;
    readyMultiMove=false;
    createEdge=false;
    findEdgeTail=false;
    moveEdgeLabel=false;
    update();
    event->accept();


}

void NSMFrame::wheelEvent(QWheelEvent *event)
{
    QPoint delta=event->angleDelta();
    int x=event->x();
    int y=event->y();
    int oriOffsetX=winOffsetX;
    int oriOffsetY=winOffsetY;
    double oriscale=winScale;
    if(delta.ry()<0){
        if(winScale>0.1)
            winScale-=0.05;
    }else{
        if(winScale<2)
            winScale+=0.05;
    }
    double nowScale=winScale;
    winOffsetX=x-(x-oriOffsetX)*nowScale/oriscale;
    winOffsetY=y-(y-oriOffsetY)*nowScale/oriscale;
    saveWinOffset();
    update();
    event->accept();
}

void NSMFrame::keyPressEvent(QKeyEvent *event)
{

}

void NSMFrame::keyReleaseEvent(QKeyEvent *event)
{

}

int NSMFrame::getWinOffsetY() const
{
    return winOffsetY;
}

void NSMFrame::setWinOffsetY(int value)
{
    winOffsetY = value;
}

int NSMFrame::getWinOffsetX() const
{
    return winOffsetX;
}

void NSMFrame::setWinOffsetX(int value)
{
    winOffsetX = value;
}

double NSMFrame::getWinScale() const
{
    return winScale;
}
void NSMFrame::init(){
    clearState();
    editable=true;
    winScale=0.5;
    winOffsetX=0;
    winOffsetY=0;
    winOriOffsetX=0;
    winOriOffsetY=0;


}
void NSMFrame::setWinScale(double value)
{
    winScale = value;
}

void NSMFrame::clearState()
{
    winStartMove=false;
    keyCtrlDown=false;
    maybeMultiSelect=false;
    multiSelect=false;
    readyMultiMove=false;
    createEdge=false;
    findEdgeTail=false;
    moveEdgeLabel=false;
}
QPoint NSMFrame::mouseToReal(int x,int y)
{
    return QPoint((x-winOffsetX)/winScale,(y-winOffsetY)/winScale);
}
QPoint NSMFrame::realToMouse(int x,int y)
{
    return QPoint(x*winScale+winOffsetX,y*winScale+winOffsetY);
}
void NSMFrame::saveWinOffset()
{
    winOriOffsetX=winOffsetX;
    winOriOffsetY=winOffsetY;
}
