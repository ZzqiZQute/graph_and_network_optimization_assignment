#ifndef FLOYDMARK_H
#define FLOYDMARK_H

#include <QList>
class FloydMark
{
public:
    FloydMark(int count);
    void setP(int x, int y, int val);
    void setD(int x, int y, int val);
    int getP(int x, int y);
    int getD(int x, int y);
    int getCount() const;
    void reset();

    int getFloydStart() const;
    void setFloydStart(int value);

    QList<int> *getVertex() const;

    void addVertex(int i);
    bool findVertex(int i);
    int getNega() const;
    void setNega(int value);

    bool getNegaCircuit() const;
    void setNegaCircuit(bool value);

private:
    int* d;
    int* p;
    int count;
    QList<int>* vertex;
    bool negaCircuit;
    int nega;
    int floydStart;

};

#endif // FLOYDMARK_H
