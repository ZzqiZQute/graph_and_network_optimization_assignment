#ifndef NSMGRAPH_H
#define NSMGRAPH_H
#include <QList>
class NSMVertex;
class BaseMatrix;
class NSMGraphData;
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
    QList<NSMGraphData *> *getGraphData() const;

    BaseMatrix *getBaseMatrix() const;
 void clearVerticesStates();
private:
    QList<NSMVertex*> *vertexs;
    BaseMatrix* baseMatrix;
    NSMVertex* dummy;
    int count;
    void calcPi();
    void changeBaseVector(int phase);
    QList<NSMGraphData*> *graphData;

    void addGraphData(int phase);
};

#endif // NSMGRAPH_H
