#include "vertex.h"
#include "vertexparams.h"
#include "common.h"
Vertex::Vertex()
{
    params=new QList<VertexParams*>();
    selected=false;
}

QList<VertexParams*>* Vertex::getParams() const
{
    return params;
}


Vertex::~Vertex(){
    delete params;
}

void Vertex::addVertexParams(VertexParams* vp){
    for(int i=0;i<params->count();i++){
        if(params->at(i)->getP()==vp->getP()){
            params->removeAt(i);
            break;
        }
    }
    params->push_back(vp);
}
void Vertex::removeVertexParamsAt(int pos){
    params->removeAt(pos);
}

int Vertex::getCenterY() const
{
    return centerY;
}

void Vertex::setCenterY(int value)
{
    centerY = value;
}

int Vertex::getCenterX() const
{
    return centerX;
}

void Vertex::setCenterX(int value)
{
    centerX = value;
}

bool Vertex::getSelected() const
{
    return selected;
}

void Vertex::setSelected(bool value)
{
    selected = value;

}

void Vertex::saveCenter()
{
    oriCenterX=centerX;
    oriCenterY=centerY;
}

int Vertex::getOriCenterX() const
{
    return oriCenterX;
}

int Vertex::getOriCenterY() const
{
    return oriCenterY;
}



