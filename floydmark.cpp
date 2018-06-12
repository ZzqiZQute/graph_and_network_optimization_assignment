#include "floydmark.h"
#include "common.h"
FloydMark::FloydMark(int count)
{
    this->count=count;
    int c=count+1;
    c*=c;
    p=new int[c];
    d=new int[c];
}
void FloydMark::setP(int x,int y,int val){
    if(x>=1&&x<=count&&y>=1&&y<=count){
        *(p+x*(count+1)+y)=val;
    }
}
void FloydMark::setD(int x,int y,int val){
    if(x>=1&&x<=count&&y>=1&&y<=count){
        *(d+x*(count+1)+y)=val;
    }
}
int FloydMark::getP(int x,int y){
    if(x>=1&&x<=count&&y>=1&&y<=count){
        return *(p+x*(count+1)+y);
    }
    return ERROR_CODE;
}
int FloydMark::getD(int x,int y){
    if(x>=1&&x<=count&&y>=1&&y<=count){
        return *(d+x*(count+1)+y);
    }
    return ERROR_CODE;
}

int FloydMark::getCount() const
{
    return count;
}
