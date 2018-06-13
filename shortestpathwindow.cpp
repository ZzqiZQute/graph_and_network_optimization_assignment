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

    display=ui->displayFrame;
    QStringList methodList;
    methodList<<"Bellman算法"<<"Floyd算法";
    ui->cbMethod->addItems(methodList);
    connect(ui->btnAddVertex,SIGNAL(clicked()),this,SLOT(onBtnAddVertexClicked()));
    connect(ui->btnRemoveAllVertex,SIGNAL(clicked()),this,SLOT(onBtnRemoveAllVertexClicked()));
}
void ShortestPathWindow::onBtnAddVertexClicked(){

    QRect rect=display->geometry();
    Graph* graph=display->getGraph();
    Vertex *v=new Vertex();
    if(graph->getCount()==0){
        v->setCenterX(VERTEX_SIZE/2);
        v->setCenterY(VERTEX_SIZE/2);

    }else{
        int lastx=graph->getLastX();
        int lasty=graph->getLastY();
        if(lastx+VERTEX_SIZE>(rect.width()*3/4-display->getWinOffsetX())/display->getWinScale()){
            v->setCenterX(VERTEX_SIZE/2);
            v->setCenterY(lasty+VERTEX_SIZE);
        }else{
            v->setCenterX(lastx+VERTEX_SIZE);
            v->setCenterY(lasty);
        }

    }
    graph->addVertex(v);
    display->setFocus();
    display->update();

}
void ShortestPathWindow::onBtnRemoveAllVertexClicked(){
    if(QMessageBox::Yes==QMessageBox::warning(parentWidget(),"警告","是否全部删除?",QMessageBox::Yes,QMessageBox::No))
    {
        Graph* graph=display->getGraph();
        graph->clearVertexs();
        display->reset();
        display->setFocus();
        display->update();
    }
}
