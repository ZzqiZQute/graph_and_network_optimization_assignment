#ifndef GRAPH_H
#define GRAPH_H
#include <QList>
class Vertex;
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

private:
    QList<Vertex*> *vertexs;
    int count;
};

#endif // GRAPH_H
