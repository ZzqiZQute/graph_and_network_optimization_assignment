#include "nsmwindow.h"
#include "ui_nsmwindow.h"
#include "launchdialog.h"
#include "setdemanddialog.h"
#include <QScreen>
#include <QMessageBox>
#include "common.h"
NSMWindow::NSMWindow(QWidget *parent) :
    mParent(parent),
    ui(new Ui::NSMWindow)
{
    setWindowFlags(windowFlags()|Qt::Window);
    ui->setupUi(this);
    QScreen* screen=QGuiApplication::primaryScreen();
    QSize size=screen->size();
    int width=geometry().width();
    int height=geometry().height();
    setGeometry((size.width()-width)/2,(size.height()-height)/2,width,height);
    init();

}
void NSMWindow::closeEvent(QCloseEvent *event){
    ((LaunchDialog*)parent())->show();
}

QWidget *NSMWindow::parent() const
{
    return mParent;
}
NSMWindow::~NSMWindow()
{
    delete ui;

}
void NSMWindow::init(){
    nsm=ui->nsm;
    connect(ui->btnAddVertex,SIGNAL(clicked()),this,SLOT(onBtnAddVertexClicked()));
    connect(ui->btnRemoveAllVertex,SIGNAL(clicked()),this,SLOT(onBtnRemoveAllVertexClicked()));
    connect(ui->rbEditMode,SIGNAL(toggled(bool)),this,SLOT(onRadioBtnEditModeToggled(bool)));
    connect(ui->btnCalculate,SIGNAL(clicked()),this,SLOT(onBtnCalcClicked()));


}
void NSMWindow::addVertex(){
    SetDemandDialog dialog(this);
    if(dialog.exec()==QDialog::Accepted){
        QRect rect=nsm->geometry();
        NSMGraph* graph=nsm->getGraph();
        NSMVertex *v=new NSMVertex();
        if(graph->getCount()==0){
            v->setCenterX(VERTEX_SIZE/2);
            v->setCenterY(VERTEX_SIZE/2);

        }else{
            int lastx=graph->getLastX();
            int lasty=graph->getLastY();
            if(lastx+VERTEX_SIZE>(rect.width()*3/8-nsm->getWinOffsetX())/nsm->getWinScale()){
                v->setCenterX(VERTEX_SIZE/2);
                v->setCenterY(lasty+VERTEX_SIZE*3);
            }else{
                v->setCenterX(lastx+VERTEX_SIZE*3/2);
                v->setCenterY(lasty);
            }

        }
        v->setBCenterY(v->getCenterY()-VERTEX_SIZE*3/2);
        v->setBCenterX(v->getCenterX());
        v->saveBCenter();
        nsm->MoveVertexLabel(v);
        int width=QFontMetrics(QFont("微软雅黑",15)).horizontalAdvance(QString::number(dialog.getDemand()));
        v->setBWidth(width+30);
        v->setB(dialog.getDemand());
        width=QFontMetrics(QFont("微软雅黑",15)).horizontalAdvance("∞");
        v->setPiWidth(width+30);
        v->setPi(POS_INFINITY);
        graph->addVertex(v);
    }

}
void NSMWindow::onBtnAddVertexClicked(){

    addVertex();
    nsm->setFocus();
    nsm->update();

}
void NSMWindow::onBtnCalcClicked(){
    ui->rbEditMode->setChecked(false);
    nsm->getGraph()->ctsma();
    nsm->update();

}
void NSMWindow::onBtnRemoveAllVertexClicked(){
    if(QMessageBox::Yes==QMessageBox::warning(this,"警告","是否全部删除?",QMessageBox::Yes,QMessageBox::No))
    {
        NSMGraph* graph=nsm->getGraph();
        graph->clearVertexs();
        nsm->reset();
        nsm->setFocus();
        nsm->update();
    }
}
void NSMWindow::onRadioBtnEditModeToggled(bool b){
    if(b){
        nsm->setEditable(true);
        ui->btnAddVertex->setEnabled(true);
        ui->btnRemoveAllVertex->setEnabled(true);
    }
    else
    {
        nsm->setEditable(false);
        ui->btnAddVertex->setEnabled(false);
        ui->btnRemoveAllVertex->setEnabled(false);
    }
    nsm->setFocus();
    nsm->update();
}
