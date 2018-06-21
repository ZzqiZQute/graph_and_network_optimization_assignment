#include "nsmvertexparam.h"

NSMVertexParam::NSMVertexParam()
{
    p=0;
    capacity=0;
    flow=0;
    cost=0;
    width=0;
}

NSMVertexParam::NSMVertexParam(int p, int c, int capacity)
{
    this->p=p;
    this->c=c;
    this->capacity=capacity;
    flow=0;
    cost=0;
    width=0;

}

int NSMVertexParam::getP() const
{
    return p;
}

void NSMVertexParam::setP(int value)
{
    p = value;
}

int NSMVertexParam::getCost() const
{
    return cost;
}

void NSMVertexParam::setCost(int value)
{
    cost = value;
}

int NSMVertexParam::getX() const
{
    return x;
}

void NSMVertexParam::setX(int value)
{
    x = value;
}

int NSMVertexParam::getY() const
{
    return y;
}

void NSMVertexParam::setY(int value)
{
    y = value;
}

double NSMVertexParam::getDeg() const
{
    return deg;
}

void NSMVertexParam::setDeg(double value)
{
    deg = value;
}

double NSMVertexParam::getDis() const
{
    return dis;
}

void NSMVertexParam::setDis(double value)
{
    dis = value;
}

int NSMVertexParam::getOrix() const
{
    return orix;
}

void NSMVertexParam::setOrix(int value)
{
    orix = value;
}

int NSMVertexParam::getOriy() const
{
    return oriy;
}

void NSMVertexParam::setOriy(int value)
{
    oriy = value;
}

bool NSMVertexParam::getMoveFlag() const
{
    return moveFlag;
}

void NSMVertexParam::setMoveFlag(bool value)
{
    moveFlag = value;
}

bool NSMVertexParam::getCurve() const
{
    return curve;
}

void NSMVertexParam::setCurve(bool value)
{
    curve = value;
}

bool NSMVertexParam::getHover() const
{
    return hover;
}

void NSMVertexParam::setHover(bool value)
{
    hover = value;
}

void NSMVertexParam::saveXY()
{
    orix=x;
    oriy=y;
}

int NSMVertexParam::getFlow() const
{
    return flow;
}

void NSMVertexParam::setFlow(int value)
{
    flow = value;
}

bool NSMVertexParam::isDummy() const
{
    return bDummy;
}

void NSMVertexParam::setDummy(bool value)
{
    bDummy = value;
}

int NSMVertexParam::getCapacity() const
{
    return capacity;
}

void NSMVertexParam::setCapacity(int value)
{
    capacity = value;
}

int NSMVertexParam::getC() const
{
    return c;
}

void NSMVertexParam::setC(int value)
{
    c = value;
}

int NSMVertexParam::getWidth() const
{
    return width;
}

void NSMVertexParam::setWidth(int value)
{
    width = value;
}
