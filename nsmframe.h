#ifndef NSMFRAME_H
#define NSMFRAME_H

#include <QFrame>
class NSMGraph;
class NSMVertex;
class NSMFrame : public QFrame
{
    Q_OBJECT
public:
    enum Type{
     DF,CV
    };
    explicit NSMFrame(QWidget* parent=0);
    ~NSMFrame();
    double getWinScale() const;
    void setWinScale(double value);
    void clearState();
    int getWinOffsetX() const;
    void setWinOffsetX(int value);

    int getWinOffsetY() const;
    void setWinOffsetY(int value);
    NSMGraph* getGraph();
    void MoveVertexLabel(NSMVertex *v);

    void reset();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    NSMGraph* graph;
    double winScale;
    int winOffsetX;
    int winOffsetY;
    int winStartOffsetX;
    int winStartOffsetY;
    int winOriOffsetX;
    int winOriOffsetY;
    int realX;
    int realY;
    int moveVertexPos;
    bool winStartMove;
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
    bool refresh;
    bool keyCtrlDown;
    bool maybeMultiSelect;
    bool multiSelect;
    bool readyMultiMove;
    bool createEdge;
    bool findEdgeTail;
    bool moveEdgeLabel;
    bool editable;
    QWidget* mParent;
    QRect painterRect;
    void drawDemandsAndArcFlows(QPainter *painter);
    void drawCostAndDualVariables(QPainter *painter);
    QPoint mouseToReal(int x, int y);
    QPoint realToMouse(int x, int y);
    void init();
    void saveWinOffset();
    void drawDemandsAndArcFlowsFrame(QPainter *painter);
    void drawCostAndDualVariablesFrame(QPainter *painter);
    void drawVertexs(QPainter *painter, Type type);
    void drawVertexsSelf(QPainter *painter);
    void drawSelects(QPainter *painter);
    int checkLBtnDownVertex();
    QPoint mouseToReal2(int x, int y);
    void drawStraightMaybeEdge(QPainter *painter, NSMVertex *v1, QPoint p);
    void drawEdges(QPainter *painter, Type type);
    void drawStraightEdge(QPainter *painter, NSMVertex *v1, NSMVertex *v2);
    void drawDemand(QPainter *painter);
    void drawDualVariable(QPainter *painter);

};

#endif // NSMFRAME_H
