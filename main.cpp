#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include "graph.h"
#include "vertex.h"
#include "vertexparams.h"

using namespace std;
int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();

    Graph *g =new Graph();
    Vertex *v=new Vertex();
    g->addVertex(v);
    v=new Vertex();
    VertexParams *vp=new VertexParams(1,1);
    v->addVertexParams(vp);
    g->addVertex(v);
    v=new Vertex();
    vp=new VertexParams(2,2);
    v->addVertexParams(vp);
    vp=new VertexParams(1,5);
    v->addVertexParams(vp);
    vp=new VertexParams(4,2);
    v->addVertexParams(vp);
    g->addVertex(v);
    v=new Vertex();
    vp=new VertexParams(5,3);
    v->addVertexParams(vp);
    g->addVertex(v);
    v=new Vertex();
    vp=new VertexParams(1,3);
    v->addVertexParams(vp);
    vp=new VertexParams(3,-4);
    v->addVertexParams(vp);
    g->addVertex(v);

    g->removeVertexAt(3);
    cout<<g->getVertexAt(4)->getParams()->at(0)->getD();


}
