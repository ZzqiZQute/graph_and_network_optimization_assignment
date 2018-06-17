#include "vertexparam.h"

VertexParam::VertexParam()
{
    p=0;
    e=0;
    x=0;
    y=0;
    hover=false;
    curve=false;
    moveFlag=false;
}

VertexParam::VertexParam(int p, int e)
{
    this->p=p;
    this->e=e;
    x=0;
    y=0;
    hover=false;
    curve=false;
    moveFlag=false;
}

int VertexParam::getP() const
{
    return p;
}

void VertexParam::setP(int value)
{
    p = value;
}

int VertexParam::getE() const
{
    return e;
}

void VertexParam::setE(int value)
{
    e = value;
}



bool VertexParam::getCurve() const
{
    return curve;
}

void VertexParam::setCurve(bool value)
{
    curve = value;
}



bool VertexParam::getMoveFlag() const
{
    return moveFlag;
}

void VertexParam::setMoveFlag(bool value)
{
    moveFlag = value;
}

int VertexParam::getY() const
{
    return y;
}

void VertexParam::setY(int value)
{
    y = value;
}

int VertexParam::getX() const
{
    return x;
}

void VertexParam::setX(int value)
{
    x = value;
}

int VertexParam::getOriy() const
{
    return oriy;
}

void VertexParam::setOriy(int value)
{
    oriy = value;
}

int VertexParam::getOrix() const
{
    return orix;
}

void VertexParam::setOrix(int value)
{
    orix = value;
}

void VertexParam::saveXY()
{
    orix=x;
    oriy=y;
}

bool VertexParam::getHover() const
{
    return hover;
}

void VertexParam::setHover(bool value)
{
    hover = value;
}

double VertexParam::getDis() const
{
    return dis;
}

void VertexParam::setDis(double value)
{
    dis = value;
}

double VertexParam::getDeg() const
{
    return deg;
}

void VertexParam::setDeg(double value)
{
    deg = value;
}




