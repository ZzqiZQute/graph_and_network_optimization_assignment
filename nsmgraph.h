#ifndef NSMGRAPH_H
#define NSMGRAPH_H
#include <QList>
class NSMVertex;
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
    void ctsma();
private:
    QList<NSMVertex*> *vertexs;
    NSMVertex* dummy;
    int count;
};

#endif // NSMGRAPH_H
