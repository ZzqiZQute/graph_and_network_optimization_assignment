#ifndef NSMWINDOW_H
#define NSMWINDOW_H

#include <QMainWindow>

namespace Ui {
class NSMWindow;
}

class NSMWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NSMWindow(QWidget *parent = 0);
    ~NSMWindow();

private:
    Ui::NSMWindow *ui;
};

#endif // NSMWINDOW_H
