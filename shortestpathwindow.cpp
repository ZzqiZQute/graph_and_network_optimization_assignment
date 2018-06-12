#include "shortestpathwindow.h"
#include "ui_shortestpathwindow.h"

ShortestPathWindow::ShortestPathWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShortestPathWindow)
{
    ui->setupUi(this);
}

ShortestPathWindow::~ShortestPathWindow()
{
    delete ui;
}
