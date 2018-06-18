#include <QApplication>
#include <iostream>
#include "launchdialog.h"
using namespace std;
int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        LaunchDialog d;
        d.show();
        return a.exec();

}
