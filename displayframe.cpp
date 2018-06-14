#include "displayframe.h"
#include "common.h"
#include "setdistancedialog.h"
#include <math.h>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <iostream>
using namespace std;
DisplayFrame::DisplayFrame(QWidget *parent):QFrame(parent)
{
    this->mParent=parent;
    graph=new Graph();
    refresh=false;
    init();
    setMouseTracking(true);

}
void DisplayFrame::init(){
    winStartMove=false;
    keyCtrlDown=false;
    maybeMultiSelect=false;
    multiSelect=false;
    readyMultiMove=false;
    createEdge=false;
    findEdgeTail=false;
    moveEdgeLabel=false;
    winScale=1;
    winOffsetX=0;
    winOffsetY=0;
    winOriOffsetX=0;
    winOriOffsetY=0;
    realX=0;
    realY=0;
    moveVertexPos=0;
    createEdgeMouseX=0;
    createEdgeMouseY=0;
    createEdgeVertexHead=0;
    createEdgeVertexTail=0;
}
DisplayFrame::~DisplayFrame(){
    delete graph;
}
void DisplayFrame::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect rect=painter.window();
    if(!refresh){
        refresh=true;
        init();
        winOffsetX=rect.width()/4-VERTEX_SIZE/2;
        winOffsetY=rect.height()/4-VERTEX_SIZE/2;
        winOriOffsetX=winOffsetX;
        winOriOffsetY=winOffsetY;
    }
    painter.fillRect(rect,Qt::white);//背景白色

    painter.translate(winOffsetX,winOffsetY);
    painter.scale(winScale,winScale);
    drawVertexs(&painter);
    drawEdge(&painter);
    drawSelects(&painter);
    event->accept();
}

void DisplayFrame::drawSelects(QPainter* painter){
    if(maybeMultiSelect){
        painter->setBrush(QBrush(QColor(128,128,128,24)));
        int xx=maybeMultiSelectMouseX;
        int xx2=maybeMultiSelectMouseX2;
        int yy=maybeMultiSelectMouseY;
        int yy2=maybeMultiSelectMouseY2;
        int x=MIN(xx,xx2);
        int y=MIN(yy,yy2);
        QPoint p=mouseToReal(x,y);
        QPoint p1=mouseToReal(xx,yy);
        QPoint p2=mouseToReal(xx2,yy2);
        int w=abs(p1.rx()-p2.rx());
        int h=abs(p1.ry()-p2.ry());
        painter->setPen(QPen(QBrush(Qt::black),0.5));
        painter->drawRect(p.rx(),p.ry(),w,h);
    }
}
void DisplayFrame::drawEdge(QPainter* painter){
    painter->setPen(QPen());
    for(int i=1;i<=graph->getCount();i++){
        Vertex* v=graph->getVertexAt(i);
        for(int i=0;i<v->getParams()->count();i++){
            VertexParams* param=v->getParams()->at(i);
            Vertex* v1=graph->getVertexAt(param->getP());
            Vertex* v2=v;
            if(param->getHover())
                painter->setPen(QColor(Qt::red));
            if(!param->getCurve()){
                drawStraightEdge(painter,v1,v2);
            }else{
                drawCurveEdge(painter,v1,v2);
            }

            painter->drawText(QRect(param->getX()-VERTEX_SIZE/2,param->getY()-VERTEX_SIZE/2,VERTEX_SIZE,VERTEX_SIZE)
                              ,QString::number(param->getE()),QTextOption(Qt::AlignCenter));
            painter->setPen(QPen());
        }
    }
    if(createEdge){
        if(!findEdgeTail){
            Vertex* v=graph->getVertexAt(createEdgeVertexHead);
            QPoint realPoint=mouseToReal(createEdgeMouseX,createEdgeMouseY);
            drawStraightMaybeEdge(painter,v,realPoint);
        }
        else{
            Vertex* v1=graph->getVertexAt(createEdgeVertexHead);
            Vertex* v2=graph->getVertexAt(createEdgeVertexTail);
            drawStraightEdge(painter,v1,v2);
        }
    }
}
QPoint DisplayFrame::calcEdgeCenter(Vertex* v1,Vertex* v2){
    return  QPoint((v1->getCenterX()+v2->getCenterX())/2,(v1->getCenterY()+v2->getCenterY())/2);
}
void DisplayFrame::drawCurveEdge(QPainter* painter,Vertex* v1,Vertex* v2)
{
    QPoint vCenter=QPoint(v1->getCenterX(),v1->getCenterY());
    int deg=calcDeg(v2->getCenterX(),v2->getCenterY(),v1->getCenterX(),v1->getCenterY());
    QPoint realPoint=calcTail(v2->getCenterX(),v2->getCenterY(),deg,VERTEX_SIZE/2);
    QPoint startPoint;
    QPoint middlePoint;
    int length=sqrt((realPoint.x()-vCenter.x())*(realPoint.x()-vCenter.x())+
                    (realPoint.y()-vCenter.y())*(realPoint.y()-vCenter.y()));
    int c=VERTEX_SIZE/2+1;
    if(length>c){
        startPoint.setX(c*(realPoint.x()-vCenter.x())/length+vCenter.x());
        startPoint.setY(c*(realPoint.y()-vCenter.y())/length+vCenter.y());

        double deg=calcDeg(startPoint.x(),startPoint.y(),realPoint.x(),realPoint.y());
        int degoffset=30;
        deg-=degoffset;
        middlePoint=calcTail(startPoint.x(),startPoint.y(),deg,length/2/cos(degoffset*PI/180));
        QPainterPath path(QPointF(startPoint.x(),startPoint.y()));
        path.quadTo(QPointF(middlePoint.x(),middlePoint.y()),QPointF(realPoint.x(),realPoint.y()));
        painter->setBrush(QBrush(Qt::transparent));
        painter->drawPath(path);
        deg=calcDeg(realPoint.x(),realPoint.y(),startPoint.x(),startPoint.y());
        deg+=degoffset;
        for(int j=-30;j<=30;j++)
        {
            QPoint p=calcTail(realPoint.x(),realPoint.y(),deg+j,VERTEX_SIZE/8/cos(j*PI/180));
            painter->drawLine(realPoint,p);
        }

    }
}
void DisplayFrame::drawStraightEdge(QPainter* painter,Vertex* v1,Vertex* v2)
{
    QPoint vCenter=QPoint(v1->getCenterX(),v1->getCenterY());
    int deg=calcDeg(v2->getCenterX(),v2->getCenterY(),v1->getCenterX(),v1->getCenterY());
    QPoint realPoint=calcTail(v2->getCenterX(),v2->getCenterY(),deg,VERTEX_SIZE/2);
    QPoint startPoint;
    int length=sqrt((realPoint.x()-vCenter.x())*(realPoint.x()-vCenter.x())+
                    (realPoint.y()-vCenter.y())*(realPoint.y()-vCenter.y()));
    int c=VERTEX_SIZE/2+1;
    if(length>c){
        startPoint.setX(c*(realPoint.x()-vCenter.x())/length+vCenter.x());
        startPoint.setY(c*(realPoint.y()-vCenter.y())/length+vCenter.y());
        painter->drawLine(startPoint,realPoint);
        double deg=calcDeg(realPoint.x(),realPoint.y(),startPoint.x(),startPoint.y());
        for(int j=-30;j<=30;j++)
        {
            QPoint p=calcTail(realPoint.x(),realPoint.y(),deg+j,VERTEX_SIZE/8/cos(j*PI/180));
            painter->drawLine(realPoint,p);
        }

    }
}
void DisplayFrame::drawStraightMaybeEdge(QPainter* painter,Vertex* v1,QPoint p){
    QPoint vCenter=QPoint(v1->getCenterX(),v1->getCenterY());
    QPoint realPoint=p;
    QPoint startPoint;
    int length=sqrt((realPoint.x()-vCenter.x())*(realPoint.x()-vCenter.x())+
                    (realPoint.y()-vCenter.y())*(realPoint.y()-vCenter.y()));
    int c=VERTEX_SIZE/2+1;
    if(length>c)
    {
        startPoint.setX(c*(realPoint.x()-vCenter.x())/length+vCenter.x());
        startPoint.setY(c*(realPoint.y()-vCenter.y())/length+vCenter.y());
        painter->drawLine(startPoint,realPoint);
        double deg=calcDeg(realPoint.x(),realPoint.y(),startPoint.x(),startPoint.y());
        for(int j=-30;j<=30;j++)
        {
            QPoint p=calcTail(realPoint.x(),realPoint.y(),deg+j,VERTEX_SIZE/8/cos(j*PI/180));
            painter->drawLine(realPoint,p);
        }

    }
}
void DisplayFrame::drawVertexs(QPainter* painter){
    QFont font=painter->font();
    painter->setFont(QFont(font.family(),15));
    for(int i=1;i<=graph->getCount();i++){
        Vertex* v=graph->getVertexAt(i);
        QRect rect;
        rect.setLeft(v->getCenterX()-VERTEX_SIZE/2);
        rect.setTop(v->getCenterY()-VERTEX_SIZE/2);
        rect.setWidth(VERTEX_SIZE);
        rect.setHeight(VERTEX_SIZE);
        if(v->getSelected()){
            painter->setBrush(QBrush(QColor(234,234,234)));
        }else{
            painter->setBrush(QBrush(QColor(Qt::white)));
        }if(keyCtrlDown){
            painter->setPen(QPen(Qt::black,2));
        }else
            painter->setPen(QPen());
        painter->drawEllipse(rect);
        painter->drawText(rect,QString::number(i),QTextOption(Qt::AlignCenter));
    }
}
int DisplayFrame::checkLBtnDownVertex(){

    int ret=0;
    for(int i=graph->getCount();i>=1;i--){
        Vertex* v=graph->getVertexAt(i);
        double dis=sqrt((realX-v->getCenterX())*(realX-v->getCenterX())+(realY-v->getCenterY())*(realY-v->getCenterY()));
        if(dis<VERTEX_SIZE/2){
            ret=i;
            break;
        }
    }
    return ret;
}
void DisplayFrame::mousePressEvent(QMouseEvent *event){
    int x=event->x();
    int y=event->y();
    if(event->button()==Qt::LeftButton){
        int pos=checkLBtnDownVertex();
        if(!keyCtrlDown){
            if(pos>0){
                Vertex* v=graph->getVertexAt(pos);
                if(!multiSelect){
                    moveVertexPos=pos;
                    moveVertexCenterX=v->getCenterX();
                    moveVertexCenterY=v->getCenterY();
                    v->setSelected(true);
                }else{
                    if(v->getSelected())
                        readyMultiMove=true;
                    else{
                        multiSelect=false;
                        for(int i=1;i<=graph->getCount();i++){
                            graph->getVertexAt(i)->setSelected(false);
                        }
                        moveVertexPos=pos;
                        moveVertexCenterX=v->getCenterX();
                        moveVertexCenterY=v->getCenterY();
                        v->setSelected(true);
                    }

                }
            }else{

                maybeMultiSelect=true;
                maybeMultiSelectMouseX=maybeMultiSelectMouseX2=x;
                maybeMultiSelectMouseY=maybeMultiSelectMouseY2=y;
                if(multiSelect){

                    multiSelect=false;
                    readyMultiMove=false;
                }
            }
            currentLMouseX=x;
            currentLMouseY=y;
            bool bBreak=false;
            for(int i=1;i<=graph->getCount();i++){
                Vertex* v=graph->getVertexAt(i);
                for(int i=0;i<v->getParams()->count();i++){
                    VertexParams* param=v->getParams()->at(i);
                    QPoint mouseReal=mouseToReal(x,y);
                    if(mouseReal.x()<param->getX()+VERTEX_SIZE/2&&
                            mouseReal.x()>param->getX()-VERTEX_SIZE/2&&
                            mouseReal.y()<param->getY()+VERTEX_SIZE/2&&
                            mouseReal.y()>param->getY()-VERTEX_SIZE/2){
                        maybeMultiSelect=false;
                        moveEdgeLabel=true;
                        param->setMoveFlag(true);
                        param->saveXY();
                        bBreak=true;
                        break;
                    }
                }
                if(bBreak)break;
            }



        }else{
            if(pos>0){
                Vertex* v=graph->getVertexAt(pos);
                v->setSelected(true);
                createEdge=true;
                createEdgeVertexHead=pos;
                createEdgeMouseX=event->x();
                createEdgeMouseY=event->y();
            }
        }

    }else if(event->button()==Qt::RightButton){
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
void DisplayFrame::reset(){
    refresh=false;
}

void DisplayFrame::mouseMoveEvent(QMouseEvent *event){
    setFocus();
    int x=event->x();
    int y=event->y();

    realX=(x-winOffsetX)/winScale;
    realY=(y-winOffsetY)/winScale;
    if(winStartMove){
        winOffsetX=winOriOffsetX+(event->x()-winStartOffsetX);
        winOffsetY=winOriOffsetY+(event->y()-winStartOffsetY);
    }
    if(maybeMultiSelect){
        bool b=false;
        maybeMultiSelectMouseX2=x;
        maybeMultiSelectMouseY2=y;
        if(!(abs(maybeMultiSelectMouseX-x)<5)||!(abs(maybeMultiSelectMouseY-y)<5))
            for(int i=1;i<=graph->getCount();i++)
            {
                int xx=graph->getVertexAt(i)->getCenterX()*winScale+winOffsetX;
                int yy=graph->getVertexAt(i)->getCenterY()*winScale+winOffsetY;
                if(((xx>maybeMultiSelectMouseX&&xx<maybeMultiSelectMouseX2)||
                    (xx>maybeMultiSelectMouseX2&&xx<maybeMultiSelectMouseX))&&
                        ((yy>maybeMultiSelectMouseY&&yy<maybeMultiSelectMouseY2)||
                         (yy>maybeMultiSelectMouseY2&&yy<maybeMultiSelectMouseY))
                        ){
                    graph->getVertexAt(i)->setSelected(true);
                    graph->getVertexAt(i)->saveCenter();
                    b=true;
                }else graph->getVertexAt(i)->setSelected(false);
            }
        if(b){
            multiSelect=true;
        }

    }
    if(readyMultiMove){
        for(int i=1;i<=graph->getCount();i++)
        {
            Vertex *v=graph->getVertexAt(i);
            if(v->getSelected()){
                v->setCenterX(v->getOriCenterX()+(x-currentLMouseX)/winScale);
                v->setCenterY(v->getOriCenterY()+(y-currentLMouseY)/winScale);
            }

        }
    }
    else if(moveVertexPos>0){
        moveEdgeLabel=false;
        Vertex *v=graph->getVertexAt(moveVertexPos);
        v->setCenterX(moveVertexCenterX+(x-currentLMouseX)/winScale);
        v->setCenterY(moveVertexCenterY+(y-currentLMouseY)/winScale);

    }
    if(createEdge){
        for(int i=1;i<=graph->getCount();i++){
            graph->getVertexAt(i)->setSelected(false);
        }
        graph->getVertexAt(createEdgeVertexHead)->setSelected(true);
        int pos=checkLBtnDownVertex();
        if(pos>0)
        {
            findEdgeTail=true;
            createEdgeVertexTail=pos;
            Vertex* v=graph->getVertexAt(pos);
            v->setSelected(true);
        }
        else{
            findEdgeTail=false;
            createEdgeMouseX=event->x();
            createEdgeMouseY=event->y();
        }
    }
    if(moveEdgeLabel){
        for(int i=1;i<=graph->getCount();i++){
            Vertex* v=graph->getVertexAt(i);
            for(int i=0;i<v->getParams()->count();i++){
                VertexParams* param=v->getParams()->at(i);
                if(param->getMoveFlag()){
                    param->setX(param->getOrix()+(x-currentLMouseX)/winScale);
                    param->setY(param->getOriy()+(y-currentLMouseY)/winScale);
                }
            }
        }
    }
    for(int i=1;i<=graph->getCount();i++){
        Vertex* v=graph->getVertexAt(i);
        for(int i=0;i<v->getParams()->count();i++){
            VertexParams* param=v->getParams()->at(i);
            param->setHover(false);
            QPoint mouseReal=mouseToReal(x,y);
            if(mouseReal.x()<param->getX()+VERTEX_SIZE/2&&
                    mouseReal.x()>param->getX()-VERTEX_SIZE/2&&
                    mouseReal.y()<param->getY()+VERTEX_SIZE/2&&
                    mouseReal.y()>param->getY()-VERTEX_SIZE/2){

                param->setHover(true);
            }
        }
    }

    update();
    event->accept();
}
void DisplayFrame::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        for(int i=1;i<=graph->getCount();i++){
            graph->getVertexAt(i)->saveCenter();
            if(!multiSelect){
                graph->getVertexAt(i)->setSelected(false);
            }
        }
        if(createEdge){
            if(findEdgeTail){
                if(createEdgeVertexHead!=createEdgeVertexTail){
                    SetDistanceDialog dialog(this);
                    dialog.exec();
                    Vertex * v=graph->getVertexAt(createEdgeVertexTail);
                    if(dialog.getOk()){
                        int dis=dialog.getDistance();
                        Vertex* v1=graph->getVertexAt(createEdgeVertexHead);
                        QPoint edgeCenter=calcEdgeCenter(v1,v);
                        int deg=calcDeg(v1->getCenterX(),v1->getCenterY(),v->getCenterX(),v->getCenterY())+90;
                        QPoint disText=calcTail(edgeCenter.x(),edgeCenter.y(),deg,VERTEX_SIZE/2);
                        VertexParams* vp=new VertexParams(createEdgeVertexHead,dis);
                        for(int i=0;i<v1->getParams()->count();i++){
                            VertexParams *vp1=v1->getParams()->at(i);
                            if(vp1->getP()==createEdgeVertexTail){
                                vp1->setCurve(true);
                                vp->setCurve(true);
                                break;
                            }
                        }
                        vp->setX(disText.x());
                        vp->setY(disText.y());
                        v->addVertexParams(vp);

                    }else{
                        for(int i=0;i<v->getParams()->count();i++){
                            if(v->getParams()->at(i)->getP()==createEdgeVertexHead){
                                for(int j=0;i<v->getParams()->count();j++){
                                    if(v->getParams()->at(j)->getP()==createEdgeVertexTail){
                                        v->getParams()->at(j)->setCurve(false);
                                        break;
                                    }
                                    v->getParams()->removeAt(i);
                                    break;
                                }
                            }
                        }
                    }
                }
                keyCtrlDown=false;
            }

        }
        for(int i=1;i<=graph->getCount();i++){
            Vertex* v=graph->getVertexAt(i);
            for(int i=0;i<v->getParams()->count();i++){
                VertexParams* param=v->getParams()->at(i);
                param->setMoveFlag(false);
            }
        }

        moveVertexPos=0;
        maybeMultiSelect=false;
        readyMultiMove=false;
        createEdge=false;
        findEdgeTail=false;
        moveEdgeLabel=false;


    }else if(event->button()==Qt::RightButton){
        winStartMove=false;
        winOriOffsetX=winOffsetX;
        winOriOffsetY=winOffsetY;
        setCursor(Qt::ArrowCursor);
    }


    update();
    event->accept();
}
void DisplayFrame::wheelEvent(QWheelEvent *event){
    QPoint delta=event->angleDelta();
    int x=event->x();
    int y=event->y();
    int oriOffsetX=winOffsetX;
    int oriOffsetY=winOffsetY;
    double oriscale=winScale;
    if(delta.ry()<0){//向下滚动
        if(winScale>0.3)
            winScale-=0.05;
    }else{//向上
        if(winScale<4)
            winScale+=0.05;
    }
    double nowScale=winScale;
    winOffsetX=x-(x-oriOffsetX)*nowScale/oriscale;
    winOffsetY=y-(y-oriOffsetY)*nowScale/oriscale;
    winOriOffsetX=winOffsetX;
    winOriOffsetY=winOffsetY;
    update();
    event->accept();
}
void DisplayFrame::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Control){
        keyCtrlDown=true;
        multiSelect=false;
        maybeMultiSelect=false;
        readyMultiMove=false;
        if(moveVertexPos!=0){
            Vertex* v=graph->getVertexAt(moveVertexPos);
            v->setSelected(false);
            moveVertexPos=0;
        }
        for(int i=1;i<=graph->getCount();i++){
            graph->getVertexAt(i)->setSelected(false);
        }
    }else if(event->key()==Qt::Key_Delete){
        for(int i=1;i<=graph->getCount();i++){
            Vertex* v=graph->getVertexAt(i);
            if(v->getSelected()){
                graph->removeVertexAt(i);
                i=0;
                continue;
            }
        }
    }
    update();
    event->accept();

}
void DisplayFrame::keyReleaseEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Control){
        keyCtrlDown=false;
        createEdge=false;
    }
    update();
    event->accept();
}

int DisplayFrame::getWinOffsetX() const
{
    return winOffsetX;
}

double DisplayFrame::getWinScale() const
{
    return winScale;
}
QPoint DisplayFrame::mouseToReal(int x,int y)
{
    return QPoint((x-winOffsetX)/winScale,(y-winOffsetY)/winScale);
}
QPoint DisplayFrame::realToMouse(int x,int y)
{
    return QPoint(x*winScale+winOffsetX,y*winScale+winOffsetY);
}
Graph *DisplayFrame::getGraph() const
{
    return graph;
}

