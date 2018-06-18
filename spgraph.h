#ifndef SPGRAPH_H
#define SPGRAPH_H
#include <QList>
class Vertex;
class BellmanMark;
class FloydMark;
using namespace std;
class SPGraph
{
public:
    SPGraph();
    ~SPGraph();
    void addVertex(Vertex* v);
    void clearVertexs();
    Vertex *getVertexAt(int pos) const;
    void removeVertexAt(int pos);
    int getCount() const;
    int bellman();
    int floyd();
    BellmanMark *getBellmanMark() const;
    FloydMark *getFloydMark() const;
    int getLastX();
    int getLastY();
    QStringList getCalcResult() const;

private:
    QList<Vertex*> *vertexs;
    BellmanMark *bellmanMark;
    FloydMark* floydMark;
    int count;
    QStringList calcResult;
};

#endif // SPGRAPH_H
