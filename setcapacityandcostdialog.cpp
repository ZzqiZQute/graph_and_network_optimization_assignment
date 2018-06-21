#include "setcapacityandcostdialog.h"
#include "ui_setcapacityandcostdialog.h"

SetCapacityAndCostDialog::SetCapacityAndCostDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetCapacityAndCostDialog)
{
    ui->setupUi(this);
}

SetCapacityAndCostDialog::~SetCapacityAndCostDialog()
{
    delete ui;
}
