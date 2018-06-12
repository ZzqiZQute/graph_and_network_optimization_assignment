#ifndef FLOYDMARK_H
#define FLOYDMARK_H


class FloydMark
{
public:
    FloydMark(int count);
    void setP(int x, int y, int val);
    void setD(int x, int y, int val);
    int getP(int x, int y);
    int getD(int x, int y);
    int getCount() const;

private:
    int* d;
    int* p;
    int count;
};

#endif // FLOYDMARK_H
