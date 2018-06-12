#include "common.h"
#include "graph.h"
#include "vertex.h"
#include "vertexparams.h"
#include <iostream>
using namespace std;
Graph::Graph()
{
    vertexs=new QList<Vertex*>();
    vertexs->push_back(new Vertex());
    count=0;
}

Graph::~Graph()
{
    vertexs->clear();
    delete vertexs;
}

void Graph::addVertex(Vertex *v)
{
    vertexs->push_back(v);
    count++;
}

void Graph::removeVertexAt(int pos){
    if(pos>0){
        for(int i=0;i<vertexs->size();i++){
            if(i!=pos){
                QList<VertexParams*> *vp=vertexs->at(i)->getParams();
                auto b=vp->begin(),e=vp->end();
                while(b!=e){
                    if((*b)->getQ()==pos)
                        vp->erase(b++);
                    else
                        b++;
                }
            }
        }
        vertexs->removeAt(pos);
        count--;
    }
}

int Graph::getCount() const
{
    return count;
}

void Graph::clearVertexs(){
    vertexs->clear();
    vertexs->push_back(new Vertex());
}

Vertex* Graph::getVertexAt(int pos) const{
    return vertexs->at(pos);
}
