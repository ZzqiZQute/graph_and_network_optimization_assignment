#ifndef SPVERTEXPARAM_H
#define SPVERTEXPARAM_H


class SPVertexParam
{
public:
    SPVertexParam();
    SPVertexParam(int p,int e);

    int getP() const;
    void setP(int value);

    int getE() const;
    void setE(int value);


    bool getCurve() const;
    void setCurve(bool value);


    bool getMoveFlag() const;
    void setMoveFlag(bool value);

    int getY() const;
    void setY(int value);

    int getX() const;
    void setX(int value);

    int getOriy() const;
    void setOriy(int value);

    int getOrix() const;
    void setOrix(int value);

    void saveXY();

    bool getHover() const;
    void setHover(bool value);



    double getDis() const;
    void setDis(double value);

    double getDeg() const;
    void setDeg(double value);

private:
    int p;//前继节点
    int e;//边长
    int x;
    int y;
    double deg;
    double dis;
    int orix;
    int oriy;
    bool moveFlag;
    bool curve;
    bool hover;

};

#endif // SPVERTEXPARAM_H
