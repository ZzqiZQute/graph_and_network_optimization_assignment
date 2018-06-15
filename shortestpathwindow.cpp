#include "shortestpathwindow.h"
#include "ui_shortestpathwindow.h"
#include "common.h"
#include <QMessageBox>
ShortestPathWindow::ShortestPathWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShortestPathWindow)
{

    ui->setupUi(this);
    init();

}

ShortestPathWindow::~ShortestPathWindow()
{
    delete ui;
}
void ShortestPathWindow::init(){

    shortestpath=ui->displayFrame;
    QStringList methodList;
    methodList<<"Bellman算法"<<"Floyd算法";
    ui->cbMethod->addItems(methodList);
    connect(ui->btnAddVertex,SIGNAL(clicked()),this,SLOT(onBtnAddVertexClicked()));
    connect(ui->btnRemoveAllVertex,SIGNAL(clicked()),this,SLOT(onBtnRemoveAllVertexClicked()));
    connect(ui->rbEditMode,SIGNAL(toggled(bool)),this,SLOT(onRadioBtnEditModeToggled(bool)));
    connect(ui->btnCalculate,SIGNAL(clicked()),this,SLOT(onBtnCalcClicked()));
}
void ShortestPathWindow::onBtnAddVertexClicked(){

    QRect rect=shortestpath->geometry();
    Graph* graph=shortestpath->getGraph();
    Vertex *v=new Vertex();
    if(graph->getCount()==0){
        v->setCenterX(VERTEX_SIZE/2);
        v->setCenterY(VERTEX_SIZE/2);

    }else{
        int lastx=graph->getLastX();
        int lasty=graph->getLastY();
        if(lastx+VERTEX_SIZE>(rect.width()*3/4-shortestpath->getWinOffsetX())/shortestpath->getWinScale()){
            v->setCenterX(VERTEX_SIZE/2);
            v->setCenterY(lasty+VERTEX_SIZE);
        }else{
            v->setCenterX(lastx+VERTEX_SIZE);
            v->setCenterY(lasty);
        }

    }
    graph->addVertex(v);
    shortestpath->setFocus();
    shortestpath->update();

}
void ShortestPathWindow::onBtnRemoveAllVertexClicked(){
    if(QMessageBox::Yes==QMessageBox::warning(parentWidget(),"警告","是否全部删除?",QMessageBox::Yes,QMessageBox::No))
    {
        Graph* graph=shortestpath->getGraph();
        graph->clearVertexs();
        shortestpath->reset();
        shortestpath->setFocus();
        shortestpath->update();
    }
}
void ShortestPathWindow::onRadioBtnEditModeToggled(bool b){
    if(b){
        shortestpath->setEditable(true);
        ui->btnAddVertex->setEnabled(true);
        ui->btnRemoveAllVertex->setEnabled(true);
    }
    else
    {
        shortestpath->setEditable(false);
        ui->btnAddVertex->setEnabled(false);
        ui->btnRemoveAllVertex->setEnabled(false);
    }
    shortestpath->setFocus();
    shortestpath->update();
}

void ShortestPathWindow::onBtnCalcClicked()
{
    ui->rbEditMode->setChecked(false);
    int i=ui->cbMethod->currentIndex();
    if(i==0){
        shortestpath->getGraph()->bellman();
        QStringList list=shortestpath->getGraph()->getCalcResult();
        ui->tbDetail->setText(list.join("\n"));
    }else if(i==1){
        shortestpath->getGraph()->floyd();
    }

}
