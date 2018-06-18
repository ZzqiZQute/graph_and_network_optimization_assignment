#ifndef BASEMATRIX_H
#define BASEMATRIX_H

#include <QList>
class BaseVector;
class BaseMatrix
{
public:
    BaseMatrix();

    QList<BaseVector*> *getVectors() const;
    void addVector(BaseVector* vector);
    void clearVectors();
    int getCount() const;
    QList<int> getCircuit(int v1,int v2);


    void removeVector(int v1, int v2);
private:
    QList<BaseVector*> *vectors;


};

#endif // BASEMATRIX_H
