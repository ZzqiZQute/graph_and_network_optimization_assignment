#include "launchdialog.h"
#include "ui_launchdialog.h"
#include "shortestpathwindow.h"
LaunchDialog::LaunchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LaunchDialog)
{
    ui->setupUi(this);
    connect(ui->btnShortestPath,SIGNAL(clicked()),this,SLOT(onBtnShortestPathClicked()));

}

LaunchDialog::~LaunchDialog()
{
    delete ui;
}
void LaunchDialog::onBtnShortestPathClicked(){
    this->close();
    ShortestPathWindow* window=new ShortestPathWindow();
    window->show();


}
