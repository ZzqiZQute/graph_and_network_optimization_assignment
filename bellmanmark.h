#ifndef BELLMANMARK_H
#define BELLMANMARK_H


class BellmanMark
{
public:
    BellmanMark(int count);
    ~BellmanMark();

    int getD(int pos);
    int getP(int pos);
    void setD(int pos, int val);
    void setP(int pos, int val);
    int getCount() const;

private:
    int *d;
    int *p;
    int count;
};

#endif // BELLMANMARK_H
