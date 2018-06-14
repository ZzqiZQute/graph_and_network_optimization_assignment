#include "setdistancedialog.h"
#include "ui_setdistancedialog.h"
#include <QRegExpValidator>
SetDistanceDialog::SetDistanceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDistanceDialog)
{
    distance=0;
    ok=false;
    ui->setupUi(this);
    QRegExp regexp("-?\\d*");
    QRegExpValidator *validator=new QRegExpValidator(regexp,this);
    ui->lineEdit->setValidator(validator);
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


void SetDistanceDialog::accept(){
    getDis();
    QDialog::accept();
}
void SetDistanceDialog::getDis(){
    QString s=ui->lineEdit->text();
    bool b;
    int i=s.toInt(&b);
    if(b){
        ok=true;
        distance=i;
    }
}

bool SetDistanceDialog::getOk() const
{
    return ok;
}
