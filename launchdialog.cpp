#include "launchdialog.h"
#include "ui_launchdialog.h"
#include "spwindow.h"
#include "nsmwindow.h"
LaunchDialog::LaunchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LaunchDialog)
{
    ui->setupUi(this);
    connect(ui->btnShortestPath,SIGNAL(clicked()),this,SLOT(onBtnShortestPathClicked()));
    connect(ui->btnNSM,SIGNAL(clicked()),this,SLOT(onBtnNSMClicked()));

}

LaunchDialog::~LaunchDialog()
{
    delete ui;
}
void LaunchDialog::onBtnShortestPathClicked(){
    this->close();
    SPWindow* window=new SPWindow();
    window->show();


}
void LaunchDialog::onBtnNSMClicked(){
    this->close();
    NSMWindow* window=new NSMWindow();
    window->show();
}
