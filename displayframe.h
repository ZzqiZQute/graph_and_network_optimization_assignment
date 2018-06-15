#ifndef DISPLAYFRAME_H
#define DISPLAYFRAME_H
#include <QFrame>
#include <QObject>
#include "graph.h"
class DisplayFrame : public QFrame
{
public:
    explicit DisplayFrame(QWidget* parent=0);

    Graph *getGraph() const;

    ~DisplayFrame();
    double getWinScale() const;

    int getWinOffsetX() const;

    void reset();
    bool getEditable() const;
    void setEditable(bool value);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    Graph* graph;
    double winScale;
    int winOffsetX;
    int winOffsetY;
    int winStartOffsetX;
    int winStartOffsetY;
    int winOriOffsetX;
    int winOriOffsetY;
    int realX;
    int realY;
    bool winStartMove;
    bool refresh;
    bool keyCtrlDown;
    bool maybeMultiSelect;
    bool multiSelect;
    bool readyMultiMove;
    bool createEdge;
    bool findEdgeTail;
    bool moveEdgeLabel;
    bool editable;
    int moveVertexPos;
    int currentLMouseX;
    int currentLMouseY;
    int moveVertexCenterX;
    int moveVertexCenterY;
    int maybeMultiSelectMouseX;
    int maybeMultiSelectMouseY;
    int maybeMultiSelectMouseX2;
    int maybeMultiSelectMouseY2;
    int createEdgeMouseX;
    int createEdgeMouseY;
    int createEdgeVertexHead;
    int createEdgeVertexTail;
    QWidget *mParent;
    void drawVertexs(QPainter *painter);
    int checkLBtnDownVertex();
    void drawTest(QPainter *painter);
    void drawSelects(QPainter *painter);
    void drawEdge(QPainter *painter);
    QPoint mouseToReal(int x, int y);
    QPoint realToMouse(int x, int y);
    void init();
    void drawStraightEdge(QPainter *painter, Vertex *v1, Vertex *v2);
    void drawStraightMaybeEdge(QPainter *painter, Vertex *v1, QPoint p);
    QPoint calcEdgeCenter(Vertex *v1, Vertex *v2);
    void drawCurveEdge(QPainter *painter, Vertex *v1, Vertex *v2);
};

#endif // DISPLAYFRAME_H
