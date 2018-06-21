#include "nsmwindow.h"
#include "ui_nsmwindow.h"
#include "launchdialog.h"
#include <QScreen>
#include "common.h"
NSMWindow::NSMWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NSMWindow)
{
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
NSMWindow::~NSMWindow()
{
    delete ui;

}
void NSMWindow::init(){
    nsm=ui->nsm;
    connect(ui->btnAddVertex,SIGNAL(clicked()),this,SLOT(onBtnAddVertexClicked()));
//    connect(ui->btnRemoveAllVertex,SIGNAL(clicked()),this,SLOT(onBtnRemoveAllVertexClicked()));
//    connect(ui->rbEditMode,SIGNAL(toggled(bool)),this,SLOT(onRadioBtnEditModeToggled(bool)));
//    connect(ui->btnCalculate,SIGNAL(clicked()),this,SLOT(onBtnCalcClicked()));


}
void NSMWindow::addVertex(){
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
            v->setCenterY(lasty+VERTEX_SIZE);
        }else{
            v->setCenterX(lastx+VERTEX_SIZE);
            v->setCenterY(lasty);
        }

    }
    graph->addVertex(v);
}
void NSMWindow::onBtnAddVertexClicked(){

    addVertex();
    nsm->setFocus();
    nsm->update();

}
