#ifndef SHORTESTPATHWINDOW_H
#define SHORTESTPATHWINDOW_H

#include <QMainWindow>

namespace Ui {
class ShortestPathWindow;
}

class ShortestPathWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShortestPathWindow(QWidget *parent = 0);
    ~ShortestPathWindow();

private:
    Ui::ShortestPathWindow *ui;
};

#endif // SHORTESTPATHWINDOW_H
