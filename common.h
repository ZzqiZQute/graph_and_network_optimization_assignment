#ifndef COMMON_H
#define COMMON_H
#define POS_INFINITY 1073741823 //max pos integer /2
#define ERROR_CODE -1073741824
#define VERTEX_SIZE 36
#define PI 3.1415926535897932
#define MIN(a,b) (a>b?b:a)
#define MAX(a,b) (a<b?b:a)
#include "graph.h"
#include "vertex.h"
#include "vertexparams.h"
#include "floydmark.h"
#include "bellmanmark.h"
double calcDeg(int x1,int y1,int x2,int y2);
QPoint calcTail(int x,int y,double deg,double len);
double calcDis(double x1, double y1, double x2, double y2);
#endif // COMMON_H
