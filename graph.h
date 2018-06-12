#ifndef GRAPH_H
#define GRAPH_H
#include <QList>
class Vertex;
class BellmanMark;
class FloydMark;
using namespace std;
class Graph
{
public:
    Graph();
    ~Graph();
    void addVertex(Vertex* v);
    void clearVertexs();
    Vertex *getVertexAt(int pos) const;
    void removeVertexAt(int pos);
    int getCount() const;
    int bellman();
    void floyd();
    BellmanMark *getBellmanMark() const;

    FloydMark *getFloydMark() const;

private:
    QList<Vertex*> *vertexs;
    BellmanMark *bellmanMark;
    FloydMark* floydMark;
    int count;
};

#endif // GRAPH_H
