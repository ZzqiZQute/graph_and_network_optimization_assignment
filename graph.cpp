#include "common.h"
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
                QList<VertexParam*> *vp=vertexs->at(i)->getParams();
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
            QList<VertexParam*> *vp=vertexs->at(i)->getParams();
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

int Graph::getCount() const
{
    return count;
}


int Graph::bellman()
{
    calcResult.clear();
    calcResult<<"当前方法:Bellman";
    if(bellmanMark!=NULL)
        delete bellmanMark;
    if(count<2){
        calcResult<<"至少要有两个节点！！！";
        return 2;
    }
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
    while(k<=count)
    {
        calcResult<<"第"+QString::number(k)+"次计算开始";
        for(int j=2;j<=count;j++){
            Vertex* v=vertexs->at(j);
            QList<VertexParam*> *vp=v->getParams();
            for(auto q=vp->begin();q!=vp->end();++q){
                int p=(*q)->getP();
                int e=(*q)->getE();
                if(m->getD(p)+e<m->getD(j)){
                    m->setD(j,m->getD(p)+e);
                    m->setP(j,p);
                    changed=true;
                }
            }
        }
        for(int j=1;j<=m->getCount();j++){
           int p=m->getP(j);
           int d=m->getD(j);
           QString s= "   ·"+QString::number(j)+":d="+(d==POS_INFINITY?"∞":QString::number(d))+" p="+QString::number(p);
           calcResult<<s;
        }
        calcResult<<"第"+QString::number(k)+"次计算结束";
        if(!changed){
            calcResult<<"完成计算";
            return 0;
        }else{
            ++k;
            changed=false;
        }
    }

    if(k>count){
        calcResult<<"检测到负权值回路，计算终止";
        return 1;
    }
    return ERROR_CODE;
}

int Graph::floyd(){
    calcResult.clear();
    calcResult<<"当前方法:Floyd";
    if(floydMark!=NULL)
        delete floydMark;
    if(count<2){
        calcResult<<"至少要有两个节点！！！";
        return ERROR_CODE;
    }
    floydMark=new FloydMark(count);
    FloydMark* m=floydMark;
    for(int i=1;i<=count;i++){
        for(int j=1;j<=count;j++){
            if(i==j)m->setD(i,j,0);
            else m->setD(i,j,POS_INFINITY);
            m->setP(i,j,i);
            Vertex* v=vertexs->at(j);
            QList<VertexParam*> *vp=v->getParams();
            for(auto k=vp->begin();k!=vp->end();++k){
                if((*k)->getP()==i){
                    m->setD(i,j,(*k)->getE());
                }
            }
        }
    }

    for(int k=1;k<=count;k++){
        for(int i=1;i<=count;i++)
            for(int j=1;j<=count;j++){
                int p=m->getD(i,k);
                int q=m->getD(k,j);
                if(p<POS_INFINITY&&q<POS_INFINITY&&p+q<m->getD(i,j)){
                    m->setD(i,j,p+q);
                    m->setP(i,j,m->getP(k,j));

                }
            }
        calcResult<<"第"+QString::number(k)+"次计算";
        calcResult<<"P:";
        QString temp="┌";
        for(int i=0;i<count;i++){
            temp+="------┬";
        }
        temp+="------┐";
        calcResult<<temp;
        temp="│      │";
        for(int i=1;i<=count-1;i++){
            temp+=QString("%1").arg(i,6)+"│";
        }
        temp+=QString("%1").arg(count,6)+"│";
        calcResult<<temp;
        for(int i=1;i<=count;i++){


            if(i==1){
                 temp="├------┼";
                 for(int j=1;j<=count-1;j++){
                     temp+="------┴";
                 }
                 temp+="------┤";
            }else{
                temp="├------┤";
                for(int j=1;j<=count-1;j++){
                    temp+="        ";
                }
                temp+="      │";

            }
            calcResult<<temp;
            temp="│"+QString("%1").arg(i,6)+"│";
            for(int j=1;j<=count-1;j++){
                temp+=QString("%1").arg(m->getP(i,j),6);
                temp+="  ";
            }
            temp+=QString("%1").arg(m->getP(i,count),6);
            temp+="│";

            calcResult<<temp;

        }
        temp="└------┴";
        for(int j=1;j<=count-1;j++){
            temp+="--------";
        }
        temp+="------┘";
        calcResult<<temp;
        calcResult<<"D:";
        temp="┌";
                for(int i=0;i<count;i++){
                    temp+="------┬";
                }
                temp+="------┐";
                calcResult<<temp;
                temp="│      │";
                for(int i=1;i<=count-1;i++){
                    temp+=QString("%1").arg(i,6)+"│";
                }
                temp+=QString("%1").arg(count,6)+"│";
                calcResult<<temp;
                for(int i=1;i<=count;i++){
                    if(i==1){
                         temp="├------┼";
                         for(int j=1;j<=count-1;j++){
                             temp+="------┴";
                         }
                         temp+="------┤";
                    }else{
                        temp="├------┤";
                        for(int j=1;j<=count-1;j++){
                            temp+="        ";
                        }
                        temp+="      │";

                    }
                    calcResult<<temp;
                    temp="│"+QString("%1").arg(i,6)+"│";
                    for(int j=1;j<=count-1;j++){
                        int d=m->getD(i,j);
                        if(d<POS_INFINITY)
                            temp+=QString("%1").arg(d,6);
                        else
                            temp+="    ∞";
                        temp+="  ";
                    }
                    int d=m->getD(i,count);
                    if(d<POS_INFINITY)
                        temp+=QString("%1").arg(d,6);
                    else
                        temp+="    ∞";
                    temp+="│";

                    calcResult<<temp;

                }
                temp="└------┴";
                for(int j=1;j<=count-1;j++){
                    temp+="--------";
                }
                temp+="------┘";
                calcResult<<temp;
    }
    calcResult<<"完成计算";
    return 0;
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

QStringList Graph::getCalcResult() const
{
    return calcResult;
}
