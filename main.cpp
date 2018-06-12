#include <QApplication>
#include <iostream>
#include "launchdialog.h"
#include "graph.h"
#include "vertex.h"
#include "vertexparams.h"
#include "bellmanmark.h"
#include "floydmark.h"
using namespace std;
int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        LaunchDialog d;
        d.show();
        return a.exec();
}
