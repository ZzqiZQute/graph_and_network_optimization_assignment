#ifndef VERTEX_H
#define VERTEX_H
#include <QList>
class VertexParam;
class Vertex
{
public:
    Vertex();
    QList<VertexParam*> *getParams() const;
    ~Vertex();
    void addVertexParams(VertexParam *vp);
    void removeVertexParamsAt(int pos);

    int getCenterY() const;
    void setCenterY(int value);

    int getCenterX() const;
    void setCenterX(int value);

    bool getSelected() const;
    void setSelected(bool value);
    void saveCenter();

    int getOriCenterX() const;

    int getOriCenterY() const;

private:
    QList<VertexParam*> *params;
    int centerX;
    int centerY;
    bool selected;
    int oriCenterX;
    int oriCenterY;

};

#endif // VERTEX_H
