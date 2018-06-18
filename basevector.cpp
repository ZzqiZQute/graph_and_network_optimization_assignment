#include "basevector.h"

BaseVector::BaseVector(int v1, int v2)
{
    this->v1=v1;
    this->v2=v2;
    bSelected=false;
}

bool BaseVector::getSelected() const
{
    return bSelected;
}

void BaseVector::setSelected(bool value)
{
    bSelected = value;
}

int BaseVector::getV1() const
{
    return v1;
}

int BaseVector::getV2() const
{
    return v2;
}
