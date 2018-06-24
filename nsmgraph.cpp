#include "common.h"

NSMGraph::NSMGraph()
{
    vertexs=new QList<NSMVertex*>();
    baseMatrix=new BaseMatrix();
    vertexs->push_back(new NSMVertex());
    graphData=new QList<NSMGraphData*>();
    count=0;
    dummy=NULL;
}

NSMGraph::~NSMGraph()
{
    vertexs->clear();
    baseMatrix->clearVectors();
    graphData->clear();
    delete graphData;
    delete baseMatrix;
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

int NSMGraph::ctsma()
{
    graphData->clear();
    dummy=new NSMVertex();
    baseMatrix->clearVectors();
    for(int i=1;i<=count;i++){
        NSMVertex* v=getVertexAt(i);
        for(int j=0;j<v->getParams()->count();j++){
            v->getParams()->at(j)->setC(v->getParams()->at(j)->getCost());
            v->getParams()->at(j)->setCost(0);
        }
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

    for(int i=1;i<count;i++){
        NSMVertex* v=getVertexAt(i);
        if(v->getB()<0)
            baseMatrix->addVector(new BaseVector(i,count));
        else
            baseMatrix->addVector(new BaseVector(count,i));
    }


    //Phase1
    changeBaseVector(1);
    int bcnt=0;
    for(int i=0;i<baseMatrix->getVectors()->count();i++){
        BaseVector* v=baseMatrix->getVectors()->at(i);
        if(v->getV1()!=count&&v->getV2()!=count)bcnt++;
    }
    if(bcnt<count-2){
        removeVertexAt(count);
        delete dummy;
        return ERROR_CODE;
    }else{
        for(auto it=baseMatrix->getVectors()->begin();it!=baseMatrix->getVectors()->end();it++){
            if((*it)->getV1()==count||(*it)->getV2()==count){
                baseMatrix->getVectors()->erase(it++);
            }
        }
        //Phase2
        removeVertexAt(count);
        delete dummy;
        for(int i=1;i<=count;i++){
            NSMVertex* v=vertexs->at(i);
            for(int j=0;j<v->getParams()->count();j++){
                NSMVertexParam* vp=v->getParams()->at(j);
                vp->setCost(vp->getC());
            }
        }
        changeBaseVector(2);
        addGraphData(2);

    }

    return 0;



}
void NSMGraph::calcPi(){

    vertexs->at(1)->setPi(0);
    for(int i=2;i<=count;i++){
        vertexs->at(i)->setPi(POS_INFINITY);
    }
    bool b=false;
    while(!b)
    {
        for(int i=1;i<=count;i++){
            for(int j=i+1;j<=count;j++){
                if(baseMatrix->isBaseVector(i,j)){
                    NSMVertex* v1=vertexs->at(i);
                    NSMVertex* v2=vertexs->at(j);
                    for(int k=0;k<v1->getParams()->count();k++){
                        NSMVertexParam* vp=v1->getParams()->at(k);
                        if(vp->getP()==j){
                            if(v1->getPi()!=POS_INFINITY&&v2->getPi()==POS_INFINITY){
                                v2->setPi(v1->getPi()-vp->getCost());
                            }
                            else if(v2->getPi()!=POS_INFINITY&&v1->getPi()==POS_INFINITY){
                                v1->setPi(v2->getPi()+vp->getCost());
                            }
                        }
                    }

                    for(int k=0;k<v2->getParams()->count();k++){
                        NSMVertexParam* vp=v2->getParams()->at(k);
                        if(vp->getP()==i){
                            if(v1->getPi()!=POS_INFINITY&&v2->getPi()==POS_INFINITY){
                                v2->setPi(v1->getPi()+vp->getCost());
                            }
                            else if(v2->getPi()!=POS_INFINITY&&v1->getPi()==POS_INFINITY){
                                v1->setPi(v2->getPi()-vp->getCost());
                            }
                        }


                    }
                }
            }
        }
        int cnt=0;
        for(int i=1;i<=count;i++){
            NSMVertex* v=vertexs->at(i);
            if(v->getPi()!=POS_INFINITY)cnt++;
        }
        if(cnt==count)b=true;
    }

}
void NSMGraph::changeBaseVector(int phase){

    bool loop=true;
    while(loop){
        addGraphData(phase);
        loop=false;
        calcPi();
        BaseVector bv;
        BaseVector bv2;
        int maxt=POS_INFINITY;
        int maxchange=POS_INFINITY;
        for(int i=1;i<=count;i++){
            NSMVertex* v=vertexs->at(i);
            for(int j=0;j<v->getParams()->count();j++){
                NSMVertexParam* vp=v->getParams()->at(j);
                if(!baseMatrix->isBaseVector(i,vp->getP())){
                    NSMVertex* v2=vertexs->at(vp->getP());
                    int t=vp->getCost()-(v->getPi()-v2->getPi());//c-(PIj-PIi)
                    vp->setRc(t);
                    if(t<0&&t<maxt){
                        loop=true;
                        bv.set(vp->getP(),i);
                        maxt=t;
                    }
                }
            }
        }
        if(!loop)break;
        QList<int> list=baseMatrix->getCircuit(bv.getV1(),bv.getV2());
        for(int i=0;i<list.count()-1;i++){
            NSMVertex* v1=vertexs->at(list.at(i));
            NSMVertex* v2=vertexs->at(list.at(i+1));
            for(int j=0;j<v1->getParams()->count();j++){
                NSMVertexParam* vp=v1->getParams()->at(j);
                if(vp->getP()==list.at(i+1)){
                    if(vp->getFlow()<=vp->getCapacity()){
                        if(vp->getCapacity()-vp->getFlow()<maxchange){
                            maxchange=vp->getCapacity()-vp->getFlow();
                            bv2.set(list.at(i),list.at(i+1));
                        }
                    }
                }

            }
            for(int j=0;j<v2->getParams()->count();j++){
                NSMVertexParam* vp=v2->getParams()->at(j);
                if(vp->getP()==list.at(i)){
                    if(vp->getFlow()>=0){
                        if(vp->getFlow()<maxchange){
                            maxchange=vp->getFlow();
                            bv2.set(list.at(i+1),list.at(i));
                        }
                    }
                }

            }


        }

        for(int i=0;i<list.count()-1;i++){
            NSMVertex* v1=vertexs->at(list.at(i));
            NSMVertex* v2=vertexs->at(list.at(i+1));
            for(int j=0;j<v1->getParams()->count();j++){
                NSMVertexParam* vp=v1->getParams()->at(j);
                if(vp->getP()==list.at(i+1)){
                    vp->setFlow(vp->getFlow()+maxchange);
                }

            }
            for(int j=0;j<v2->getParams()->count();j++){
                NSMVertexParam* vp=v2->getParams()->at(j);
                if(vp->getP()==list.at(i)){
                    vp->setFlow(vp->getFlow()-maxchange);
                }

            }

        }
        NSMVertex* v3=vertexs->at(bv.getV2());
        for(int i=0;i<v3->getParams()->count();i++){
            NSMVertexParam* vp3=v3->getParams()->at(i);
            if(vp3->getP()==bv.getV1()){
                vp3->setFlow(vp3->getFlow()+maxchange);
                break;
            }
        }

        baseMatrix->removeVector(bv2.getV1(),bv2.getV2());
        baseMatrix->addVector(new BaseVector(bv.getV1(),bv.getV2()));


    }

}

QList<NSMGraphData *> *NSMGraph::getGraphData() const
{
    return graphData;
}

BaseMatrix *NSMGraph::getBaseMatrix() const
{
    return baseMatrix;
}

void NSMGraph::clearVerticesStates()
{
    for(int i=1;i<=count;i++){
        NSMVertex* v=getVertexAt(i);
        for(int j=0;j<v->getParams()->count();j++){
            NSMVertexParam* vp=v->getParams()->at(j);
            vp->setMoveCFlag(false);
            vp->setMoveFFlag(false);
        }
    }
}

int NSMGraph::getLastX()
{
    return vertexs->at(count)->getCenterX();
}

int NSMGraph::getLastY()
{
    return vertexs->at(count)->getCenterY();
}
void NSMGraph::addGraphData(int phase){
    NSMGraphData* gd=new NSMGraphData(phase);
    for(int i=1;i<=count;i++){
        NSMVertex* v=getVertexAt(i);
        NSMVertexData* vd=new NSMVertexData();
        vd->setB(v->getB());
        vd->setPi(v->getPi());
        for(int j=0;j<v->getParams()->count();j++){
            NSMVertexParam* p=v->getParams()->at(j);
            NSMVertexParamData* pd=new NSMVertexParamData();
            pd->setC(p->getC());
            pd->setCapacity(p->getCapacity());
            pd->setCost(p->getCost());
            pd->setFlow(p->getFlow());
            pd->setP(p->getP());
            pd->setRc(p->getRc());
            vd->getParams()->append(pd);

        }
        gd->getVertexDatas()->append(vd);

    }


    for(int i=0;i<baseMatrix->getVectors()->count();i++){
        gd->getBaseMatrix()->addVector(baseMatrix->getVectors()->at(i));
    }
    graphData->append(gd);
}
