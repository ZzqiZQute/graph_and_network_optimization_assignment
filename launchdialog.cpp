#include "launchdialog.h"
#include "ui_launchdialog.h"
#include "spwindow.h"
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
    SPWindow* window=new SPWindow();
    window->show();


}
