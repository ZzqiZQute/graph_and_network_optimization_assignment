#ifndef SPWINDOW_H
#define SPWINDOW_H

#include <QMainWindow>
class SPFrame;
namespace Ui {
class SPWindow;
}

class SPWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SPWindow(QWidget *parent = 0);
    ~SPWindow();

public slots:
    void onBtnAddVertexClicked();
    void onBtnRemoveAllVertexClicked();
    void onRadioBtnEditModeToggled(bool);
    void onBtnCalcClicked();
    void onActionOpen();
    void onActionSave();
    void onActionLoad();
    void onHintChanged(QString str);
private:
    Ui::SPWindow *ui;
    void init();
    SPFrame *shortestpath;
    void makeHintText(QStringList list);
    void addVertex();
};

#endif // SPWINDOW_H
