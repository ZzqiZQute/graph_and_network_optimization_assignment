#include "setdistancedialog.h"
#include "ui_setdistancedialog.h"
#include <QRegExpValidator>
SetDistanceDialog::SetDistanceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDistanceDialog)
{
    ui->setupUi(this);
    QRegExp regexp("-?\\d*");
    QRegExpValidator *validator=new QRegExpValidator(regexp,this);
    ui->lineEdit->setValidator(validator);
    hasValue=false;
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(onBtnOkClicked()));


}

SetDistanceDialog::~SetDistanceDialog()
{
    delete ui;
}

int SetDistanceDialog::getDistance() const
{
    return distance;
}

void SetDistanceDialog::onBtnOkClicked(){
    getDis();
    this->close();
}

bool SetDistanceDialog::getHasValue() const
{
    return hasValue;
}
void SetDistanceDialog::accept(){
    getDis();
    QDialog::accept();
}
void SetDistanceDialog::getDis(){
    QString s=ui->lineEdit->text();
    bool b;
    int i=s.toInt(&b);
    if(b){
        distance=i;
        hasValue=true;
    }
}
