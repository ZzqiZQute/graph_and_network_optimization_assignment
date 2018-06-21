#ifndef NSMWINDOW_H
#define NSMWINDOW_H

#include <QMainWindow>
class NSMFrame;
namespace Ui {
class NSMWindow;
}

class NSMWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit NSMWindow(QWidget *parent = 0);
    ~NSMWindow();

    QWidget *parent() const;

public slots:
    void onBtnAddVertexClicked();
protected:
    void closeEvent(QCloseEvent *event);
private:
    QWidget* mParent;
    Ui::NSMWindow *ui;
    NSMFrame* nsm;
    void init();
    void addVertex();
};

#endif // NSMWINDOW_H
