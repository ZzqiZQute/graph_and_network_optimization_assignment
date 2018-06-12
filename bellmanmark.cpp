#include "bellmanmark.h"
#include "common.h"
BellmanMark::BellmanMark(int count)
{
    this->count=count;
    d=new int[count+1];
    p=new int[count+1];
}

BellmanMark::~BellmanMark(){
    delete d;
    delete p;
}
int BellmanMark::getD(int pos){
    if(pos>=1&&pos<=count)
        return *(d+pos);
    return ERROR_CODE;
}
int BellmanMark::getP(int pos){
    if(pos>=1&&pos<=count)
        return *(p+pos);
     return ERROR_CODE;
}
void BellmanMark::setD(int pos,int val){
    if(pos>=1&&pos<=count)
        *(d+pos)=val;
}
void BellmanMark::setP(int pos,int val){
    if(pos>=1&&pos<=count)
        *(p+pos)=val;
}

int BellmanMark::getCount() const
{
    return count;
}
