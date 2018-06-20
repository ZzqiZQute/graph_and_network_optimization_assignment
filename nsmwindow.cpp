#include "nsmwindow.h"
#include "ui_nsmwindow.h"

NSMWindow::NSMWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NSMWindow)
{
    ui->setupUi(this);

}

NSMWindow::~NSMWindow()
{
    delete ui;
}
