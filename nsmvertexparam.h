#ifndef NSMVERTEXPARAM_H
#define NSMVERTEXPARAM_H

#include "common.h"
class NSMVertexParam
{
public:
    NSMVertexParam();
    NSMVertexParam(int p, int c=0,int capacity=POS_INFINITY);
    int getP() const;
    void setP(int value);

    int getCost() const;
    void setCost(int value);



    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    double getDeg() const;
    void setDeg(double value);

    double getDis() const;
    void setDis(double value);

    int getOrix() const;
    void setOrix(int value);

    int getOriy() const;
    void setOriy(int value);

    bool getMoveFlag() const;
    void setMoveFlag(bool value);

    bool getCurve() const;
    void setCurve(bool value);

    bool getHover() const;
    void setHover(bool value);


    void saveXY();

    int getFlow() const;
    void setFlow(int value);

    bool isDummy() const;
    void setDummy(bool value);

    int getCapacity() const;
    void setCapacity(int value);

    int getC() const;
    void setC(int value);

    int getWidth() const;
    void setWidth(int value);

private:
    int p;
    int capacity;
    int c;
    int cost;
    int flow;
    int x;
    int y;
    int width;
    double deg;
    double dis;
    int orix;
    int oriy;
    bool moveFlag;
    bool curve;
    bool hover;
    bool bDummy;
};

#endif // NSMVERTEXPARAM_H
