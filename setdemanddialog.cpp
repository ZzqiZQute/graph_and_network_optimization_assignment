#include "setdemanddialog.h"
#include "ui_setdemanddialog.h"
#include <QRegExpValidator>
SetDemandDialog::SetDemandDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDemandDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("-?\\d{1,8}"),this));
    connect(ui->btnOK,SIGNAL(clicked()),this,SLOT(onBtnOkClicked()));
}

SetDemandDialog::~SetDemandDialog()
{
    delete ui;
}
void SetDemandDialog::onBtnOkClicked(){
    bool b;
    demand=ui->lineEdit->text().toInt(&b);
    if(!b){
        demand=0;
    }
    this->accept();

}

int SetDemandDialog::getDemand() const
{
    return demand;
}

