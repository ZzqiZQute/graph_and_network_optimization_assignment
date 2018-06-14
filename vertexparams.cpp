#include "vertexparams.h"

VertexParams::VertexParams()
{
    p=0;
    e=0;
    x=0;
    y=0;
    hover=false;
    curve=false;
    moveFlag=false;
}

VertexParams::VertexParams(int p, int e)
{
    this->p=p;
    this->e=e;
    x=0;
    y=0;
    hover=false;
    curve=false;
    moveFlag=false;
}

int VertexParams::getP() const
{
    return p;
}

void VertexParams::setP(int value)
{
    p = value;
}

int VertexParams::getE() const
{
    return e;
}

void VertexParams::setE(int value)
{
    e = value;
}



bool VertexParams::getCurve() const
{
    return curve;
}

void VertexParams::setCurve(bool value)
{
    curve = value;
}



bool VertexParams::getMoveFlag() const
{
    return moveFlag;
}

void VertexParams::setMoveFlag(bool value)
{
    moveFlag = value;
}

int VertexParams::getY() const
{
    return y;
}

void VertexParams::setY(int value)
{
    y = value;
}

int VertexParams::getX() const
{
    return x;
}

void VertexParams::setX(int value)
{
    x = value;
}

int VertexParams::getOriy() const
{
    return oriy;
}

void VertexParams::setOriy(int value)
{
    oriy = value;
}

int VertexParams::getOrix() const
{
    return orix;
}

void VertexParams::setOrix(int value)
{
    orix = value;
}

void VertexParams::saveXY()
{
    orix=x;
    oriy=y;
}

bool VertexParams::getHover() const
{
    return hover;
}

void VertexParams::setHover(bool value)
{
    hover = value;
}



