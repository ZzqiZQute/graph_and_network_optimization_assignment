#ifndef NSMVERTEXPARAM_H
#define NSMVERTEXPARAM_H


class NSMVertexParam
{
public:
    NSMVertexParam();
    NSMVertexParam(int p, int capacity=-1);
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

private:
    int p;
    int capacity;
    int cost;
    int flow;
    int x;
    int y;
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
