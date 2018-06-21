#include "common.h"

NSMVertex::NSMVertex()
{
    b=0;
    pi=POS_INFINITY;
    selected=false;
    params=new QList<NSMVertexParam*>();

}

NSMVertex::NSMVertex(int b)
{
    this->b=b;
    pi=POS_INFINITY;
    selected=false;
    params=new QList<NSMVertexParam*>();
}

NSMVertex::~NSMVertex()
{
    params->clear();
    delete params;
}

QList<NSMVertexParam *> *NSMVertex::getParams() const
{
    return params;
}

void NSMVertex::addVertexParams(NSMVertexParam *vp)
{
    for(int i=0;i<params->count();i++){
        if(params->at(i)->getP()==vp->getP()){
            params->removeAt(i);
            break;
        }
    }
    params->push_back(vp);
}

void NSMVertex::removeVertexParamsAt(int pos)
{
    params->removeAt(pos);
}

int NSMVertex::getB() const
{
    return b;
}

void NSMVertex::setB(int value)
{
    b = value;
}

int NSMVertex::getPi() const
{
    return pi;
}

void NSMVertex::setPi(int value)
{
    pi = value;
}

int NSMVertex::getCenterX() const
{
    return centerX;
}

void NSMVertex::setCenterX(int value)
{
    centerX = value;
}

int NSMVertex::getCenterY() const
{
    return centerY;
}

void NSMVertex::setCenterY(int value)
{
    centerY = value;
}

bool NSMVertex::getSelected() const
{
    return selected;
}

void NSMVertex::setSelected(bool value)
{
    selected = value;
}

int NSMVertex::getOriCenterX() const
{
    return oriCenterX;
}

void NSMVertex::setOriCenterX(int value)
{
    oriCenterX = value;
}

int NSMVertex::getOriCenterY() const
{
    return oriCenterY;
}

void NSMVertex::setOriCenterY(int value)
{
    oriCenterY = value;
}

void NSMVertex::saveCenter()
{
    oriCenterX=centerX;
    oriCenterY=centerY;
}

int NSMVertex::getBCenterX() const
{
    return bCenterX;
}

void NSMVertex::setBCenterX(int value)
{
    bCenterX = value;
}

int NSMVertex::getBCenterY() const
{
    return bCenterY;
}

void NSMVertex::setBCenterY(int value)
{
    bCenterY = value;
}

int NSMVertex::getBWidth() const
{
    return bWidth;
}

void NSMVertex::setBWidth(int value)
{
    bWidth = value;
}
