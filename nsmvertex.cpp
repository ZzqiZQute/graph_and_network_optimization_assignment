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
