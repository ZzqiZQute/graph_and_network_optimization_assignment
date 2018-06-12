#include "vertex.h"
#include "vertexparams.h"
Vertex::Vertex()
{
    params=new QList<VertexParams*>();
}

QList<VertexParams*>* Vertex::getParams() const
{
    return params;
}


Vertex::~Vertex(){
    delete params;
}

void Vertex::addVertexParams(VertexParams* vp){
    params->push_back(vp);
}
void Vertex::removeVertexParamsAt(int pos){
    params->removeAt(pos);
}
