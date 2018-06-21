#ifndef NSMFRAME_H
#define NSMFRAME_H

#include <QFrame>

class NSMFrame : public QFrame
{
    Q_OBJECT
public:
    explicit NSMFrame(QWidget* parent=0);
    double getWinScale() const;
    void setWinScale(double value);
    void clearState();
    int getWinOffsetX() const;
    void setWinOffsetX(int value);

    int getWinOffsetY() const;
    void setWinOffsetY(int value);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    double winScale;
    int winOffsetX;
    int winOffsetY;
    int winStartOffsetX;
    int winStartOffsetY;
    int winOriOffsetX;
    int winOriOffsetY;
    int moveVertexPos;
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
    QWidget* mParent;
    void drawDemandAndArcFlows(QPainter *painter);
    void drawCostAndDualVariables(QPainter *painter);
    QPoint mouseToReal(int x, int y);
    QPoint realToMouse(int x, int y);
    void init();
    void saveWinOffset();
};

#endif // NSMFRAME_H
