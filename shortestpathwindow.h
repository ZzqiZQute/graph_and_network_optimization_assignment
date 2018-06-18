#ifndef SHORTESTPATHWINDOW_H
#define SHORTESTPATHWINDOW_H

#include <QMainWindow>
class DisplayFrame;
namespace Ui {
class ShortestPathWindow;
}

class ShortestPathWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShortestPathWindow(QWidget *parent = 0);
    ~ShortestPathWindow();

public slots:
    void onBtnAddVertexClicked();
    void onBtnRemoveAllVertexClicked();
    void onRadioBtnEditModeToggled(bool);
    void onBtnCalcClicked();
    void onActionOpen();
    void onActionSave();
private:
    Ui::ShortestPathWindow *ui;
    void init();
    DisplayFrame *shortestpath;
    void makeHintText(QStringList list);
};

#endif // SHORTESTPATHWINDOW_H
