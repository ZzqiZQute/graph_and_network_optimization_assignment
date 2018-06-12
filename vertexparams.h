#ifndef VERTEXPARAMS_H
#define VERTEXPARAMS_H


class VertexParams
{
public:
    VertexParams();
    VertexParams(int p,int e);

    int getP() const;
    void setP(int value);

    int getE() const;
    void setE(int value);


private:
    int p;//前继节点
    int e;//边长

};

#endif // VERTEXPARAMS_H
