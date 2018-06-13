#include "common.h"
#include "graph.h"
#include "vertex.h"
#include "vertexparams.h"
#include "bellmanmark.h"
#include "floydmark.h"
#include <iostream>
using namespace std;
Graph::Graph()
{
    vertexs=new QList<Vertex*>();
    vertexs->push_back(new Vertex());
    bellmanMark=NULL;
    floydMark=NULL;
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
                    if((*b)->getP()==pos)
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


int Graph::bellman()
{
    if(bellmanMark!=NULL)
        delete bellmanMark;
    int k=1;
    bool changed=false;
    bellmanMark=new BellmanMark(count);
    BellmanMark* m=bellmanMark;
    m->setD(1,0);
    m->setP(1,0);
    for(int i=2;i<=count;i++){
        m->setD(i,POS_INFINITY);
        m->setP(i,0);
    }
    while(k<count)
    {
        for(int j=1;j<=count;j++){
            Vertex* v=vertexs->at(j);
            QList<VertexParams*> *vp=v->getParams();
            for(auto k=vp->begin();k!=vp->end();++k){
                int p=(*k)->getP();
                int e=(*k)->getE();
                if(m->getD(p)+e<m->getD(j)){
                    m->setD(j,m->getP(p)+e);
                    m->setP(j,p);
                    changed=true;
                }
            }
        }
        if(!changed){
            return 0;
        }else{
            ++k;
            changed=false;
        }
    }

    if(k>=count){
        return 1;
    }
    return 2;
}

void Graph::floyd(){
    if(floydMark!=NULL)
        delete floydMark;
    floydMark=new FloydMark(count);
    FloydMark* m=floydMark;
    for(int i=1;i<=count;i++){
        for(int j=1;j<=count;j++){
            if(i==j)m->setD(i,j,0);
            else m->setD(i,j,POS_INFINITY);
            m->setP(i,j,i);
            Vertex* v=vertexs->at(j);
            QList<VertexParams*> *vp=v->getParams();
            for(auto k=vp->begin();k!=vp->end();++k){
                if((*k)->getP()==i){
                    m->setD(i,j,(*k)->getE());
                }
            }
        }
    }

    for(int k=1;k<=count;k++)
        for(int i=1;i<=count;i++)
            for(int j=1;j<=count;j++){
                int p=m->getD(i,k);
                int q=m->getD(k,j);
                if(p<POS_INFINITY&&q<POS_INFINITY&&p+q<m->getD(i,j)){
                    m->setD(i,j,p+q);
                    m->setP(i,j,m->getP(k,j));

                }
            }
}

BellmanMark *Graph::getBellmanMark() const
{
    return bellmanMark;
}

FloydMark *Graph::getFloydMark() const
{
    return floydMark;
}




void Graph::clearVertexs(){
    vertexs->clear();
    vertexs->push_back(new Vertex());
    count=0;
}

Vertex* Graph::getVertexAt(int pos) const{
    return vertexs->at(pos);
}
int Graph::getLastX(){

    return vertexs->at(count)->getCenterX();
}
int Graph::getLastY(){

   return vertexs->at(count)->getCenterY();
}
