#include "common.h"
#include <math.h>
double calcDeg(int x1,int y1,int x2,int y2){
    double ret=0;
    if(abs(x1-x2)<=1&&abs(y1-y2)>1) ret= y2>y1?-90:90;
    else if(abs(y1-y2)<=1&&abs(x1-x2)>1) ret= x2>x1?0:180;
    else{
        ret=atan((double)(y1-y2)/(x2-x1))*180/PI;
        if(x1>x2){
           ret+=180;
        }
    }
    if(ret>180)ret-=360;
    return ret;
}
QPoint calcTail(int x,int y,double deg,double len){
    return QPoint(x+len*cos(deg*PI/180),y-len*sin(deg*PI/180));
}
