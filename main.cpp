#include <QApplication>
#include <iostream>
#include "launchdialog.h"
#include "basematrix.h"
#include "basevector.h"
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    LaunchDialog d;
//    d.show();
//    return a.exec();
    BaseMatrix *matrix=new BaseMatrix();
    BaseVector *vector=new BaseVector(1,2);
    matrix->addVector(vector);
    vector=new BaseVector(1,8);
    matrix->addVector(vector);
    vector=new BaseVector(1,7);
    matrix->addVector(vector);
    vector=new BaseVector(2,3);
    matrix->addVector(vector);
    vector=new BaseVector(2,5);
    matrix->addVector(vector);
    vector=new BaseVector(4,7);
    matrix->addVector(vector);
    vector=new BaseVector(7,6);
    matrix->addVector(vector);
    QList<int> list=matrix->getCircuit(4,6);
    for(int i=0;i<list.count();i++){
        cout<<list.at(i)<<" ";
    }
    return 0;


}
