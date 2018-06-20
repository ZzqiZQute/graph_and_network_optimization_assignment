#include <QApplication>
#include <iostream>
#include "launchdialog.h"
#include "common.h"
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LaunchDialog d;
    d.show();
    return a.exec();
//    NSMGraph *graph=new NSMGraph();
//    NSMVertex *v=new NSMVertex(-4);
//    graph->addVertex(v);
//    v=new NSMVertex(-2);
//    NSMVertexParam *vp=new NSMVertexParam(1,3);
//    v->addVertexParams(vp);
//    vp=new NSMVertexParam(5,3);
//    v->addVertexParams(vp);
//    graph->addVertex(v);
//    v=new NSMVertex(1);
//    vp=new NSMVertexParam(1,1);
//    v->addVertexParams(vp);
//    vp=new NSMVertexParam(4,1);
//    v->addVertexParams(vp);
//    graph->addVertex(v);
//    v=new NSMVertex();
//    vp=new NSMVertexParam(2,1);
//    v->addVertexParams(vp);
//    graph->addVertex(v);
//    v=new NSMVertex(5);
//    vp=new NSMVertexParam(4,5);
//    v->addVertexParams(vp);
//    vp=new NSMVertexParam(3,2);
//    v->addVertexParams(vp);
//    graph->addVertex(v);
//    graph->ctsma();

//    return 0;



}
