#ifndef NSMGRAPH_H
#define NSMGRAPH_H
#include <QList>
class NSMVertex;
class BaseMatrix;
class NSMGraph
{
public:
    NSMGraph();
    ~NSMGraph();
    void addVertex(NSMVertex* v);
    void clearVertexs();
    NSMVertex *getVertexAt(int pos) const;
    void removeVertexAt(int pos);
    int getCount() const;
    int ctsma();
    int getLastX();
    int getLastY();
private:
    QList<NSMVertex*> *vertexs;
    BaseMatrix* baseMatrix;
    NSMVertex* dummy;
    int count;
    void calcPi();
    void changeBaseVector();

};

#endif // NSMGRAPH_H
