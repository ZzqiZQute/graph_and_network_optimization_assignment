#ifndef VERTEX_H
#define VERTEX_H
#include <QList>
class VertexParams;
class Vertex
{
public:
    Vertex();
    QList<VertexParams*> *getParams() const;
    ~Vertex();
    void addVertexParams(VertexParams *vp);
    void removeVertexParamsAt(int pos);

private:
    QList<VertexParams*> *params;

};

#endif // VERTEX_H
