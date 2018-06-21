#ifndef NSMVERTEX_H
#define NSMVERTEX_H
#include <QList>
class NSMVertexParam;
class NSMVertex
{
public:
    NSMVertex();
    NSMVertex(int b);
    ~NSMVertex();
    QList<NSMVertexParam *> *getParams() const;
    void addVertexParams(NSMVertexParam *vp);
    void removeVertexParamsAt(int pos);
    int getB() const;
    void setB(int value);

    int getPi() const;
    void setPi(int value);

    int getCenterX() const;
    void setCenterX(int value);

    int getCenterY() const;
    void setCenterY(int value);

    bool getSelected() const;
    void setSelected(bool value);

    int getOriCenterX() const;
    void setOriCenterX(int value);

    int getOriCenterY() const;
    void setOriCenterY(int value);

    void saveCenter();
    int getBCenterX() const;
    void setBCenterX(int value);

    int getBCenterY() const;
    void setBCenterY(int value);

    int getBWidth() const;
    void setBWidth(int value);

private:
    QList<NSMVertexParam*> *params;
    int b;
    int pi;
    int centerX;
    int centerY;
    bool selected;
    int oriCenterX;
    int oriCenterY;
    int bCenterX;
    int bCenterY;
    int bWidth;
};

#endif // NSMVERTEX_H
