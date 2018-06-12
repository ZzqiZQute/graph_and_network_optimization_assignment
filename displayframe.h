#ifndef DISPLAYFRAME_H
#define DISPLAYFRAME_H
#include <QFrame>
#include <QObject>

class DisplayFrame : public QFrame
{
public:
    explicit DisplayFrame(QWidget* parent=0);
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // DISPLAYFRAME_H
