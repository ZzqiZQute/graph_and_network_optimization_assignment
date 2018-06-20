#ifndef NSMFRAME_H
#define NSMFRAME_H

#include <QFrame>

class NSMFrame : public QFrame
{
    Q_OBJECT
public:
    explicit NSMFrame(QWidget* parent=0);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    QWidget* mParent;
    bool refresh;
    void drawDemandAndArcFlows(QPainter *painter);
    void drawCostAndDualVariables(QPainter *painter);
};

#endif // NSMFRAME_H
