#include "vertexparams.h"

VertexParams::VertexParams()
{

}

VertexParams::VertexParams(int p, int e)
{
    this->p=p;
    this->e=e;
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



