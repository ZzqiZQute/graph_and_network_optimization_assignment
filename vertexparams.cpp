#include "vertexparams.h"

VertexParams::VertexParams()
{

}

VertexParams::VertexParams(int q, int d)
{
    this->q=q;
    this->d=d;
}

int VertexParams::getQ() const
{
    return q;
}

void VertexParams::setQ(int value)
{
    q = value;
}

int VertexParams::getD() const
{
    return d;
}

void VertexParams::setD(int value)
{
    d = value;
}
