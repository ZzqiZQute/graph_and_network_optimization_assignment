#ifndef NSMGRAPHDATA_H
#define NSMGRAPHDATA_H
#include <QList>
class NSMVertexData;
class BaseMatrix;
class NSMGraphData
{
public:
    NSMGraphData(int phase);
    ~NSMGraphData();
    int getPhase() const;
    void setPhase(int value);

    QList<NSMVertexData *> *getVertexDatas() const;

    BaseMatrix *getBaseMatrix() const;
    void setBaseMatrix(BaseMatrix *value);

private:
    QList<NSMVertexData*> *vertexDatas;
    BaseMatrix* baseMatrix;
    int phase;
};

#endif // NSMGRAPHDATA_H
