#include "common.h"

NSMGraph::NSMGraph()
{
    vertexs=new QList<NSMVertex*>();
    vertexs->push_back(new NSMVertex());
    count=0;
    dummy=NULL;
}

NSMGraph::~NSMGraph()
{
    vertexs->clear();
    delete vertexs;
}

void NSMGraph::addVertex(NSMVertex *v)
{
    vertexs->push_back(v);
    count++;
}

void NSMGraph::clearVertexs()
{
    vertexs->clear();
    vertexs->push_back(new NSMVertex());
    count=0;
}

NSMVertex *NSMGraph::getVertexAt(int pos) const
{
     return vertexs->at(pos);
}

void NSMGraph::removeVertexAt(int pos)
{
    if(pos>0){
        for(int i=0;i<vertexs->size();i++){
            if(i!=pos){
                QList<NSMVertexParam*> *vp=vertexs->at(i)->getParams();
                auto b=vp->begin(),e=vp->end();
                while(b!=e){
                    if((*b)->getP()==pos)
                        vp->erase(b++);
                    else
                        b++;
                }
            }
        }
       for(int i=0;i<vertexs->size();i++){
            QList<NSMVertexParam*> *vp=vertexs->at(i)->getParams();
            auto b=vp->begin(),e=vp->end();
            while(b!=e){
                if((*b)->getP()>pos)
                    (*b)->setP((*b)->getP()-1);
                b++;
            }
        }
        vertexs->removeAt(pos);
        count--;
    }
}

int NSMGraph::getCount() const
{
    return count;
}

void NSMGraph::ctsma()
{
    if(dummy!=NULL){
        removeVertexAt(count);
        delete dummy;
    }
    dummy=new NSMVertex();
    for(int i=1;i<=count;i++){
        NSMVertex* v=getVertexAt(i);
        if(v->getB()<0){
            NSMVertexParam* vp=new NSMVertexParam(i);
            vp->setFlow(-v->getB());
            vp->setCost(1);
            dummy->addVertexParams(vp);
        }else{
            NSMVertexParam* vp=new NSMVertexParam(count+1);
            vp->setFlow(v->getB());
            vp->setCost(1);
            v->addVertexParams(vp);
        }
    }
    addVertex(dummy);
}
