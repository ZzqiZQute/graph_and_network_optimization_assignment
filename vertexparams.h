#ifndef VERTEXPARAMS_H
#define VERTEXPARAMS_H


class VertexParams
{
public:
    VertexParams();
    VertexParams(int q,int d);


    int getQ() const;
    void setQ(int value);

    int getD() const;
    void setD(int value);

private:
    int q;//前继节点
    int d;//距离
};

#endif // VERTEXPARAMS_H
