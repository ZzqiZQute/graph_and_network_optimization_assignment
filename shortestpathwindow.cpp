#include "shortestpathwindow.h"
#include "ui_shortestpathwindow.h"
#include "common.h"
#include <QMessageBox>
#include <QGuiApplication>
#include <QScreen>
#include <QFileDialog>
#include <QTextCodec>
ShortestPathWindow::ShortestPathWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShortestPathWindow)
{

    ui->setupUi(this);
    QScreen* screen=QGuiApplication::primaryScreen();
    QSize size=screen->size();
    int width=geometry().width();
    int height=geometry().height();
    setGeometry((size.width()-width)/2,(size.height()-height)/2,width,height);
    init();

}

ShortestPathWindow::~ShortestPathWindow()
{
    delete ui;
}
void ShortestPathWindow::init(){

    shortestpath=ui->displayFrame;
    QStringList methodList;
    methodList<<"Bellman"<<"Floyd";
    ui->cbMethod->addItems(methodList);
    ui->rbEditMode->setEnabled(false);
    connect(ui->btnAddVertex,SIGNAL(clicked()),this,SLOT(onBtnAddVertexClicked()));
    connect(ui->btnRemoveAllVertex,SIGNAL(clicked()),this,SLOT(onBtnRemoveAllVertexClicked()));
    connect(ui->rbEditMode,SIGNAL(toggled(bool)),this,SLOT(onRadioBtnEditModeToggled(bool)));
    connect(ui->btnCalculate,SIGNAL(clicked()),this,SLOT(onBtnCalcClicked()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(onActionOpen()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(onActionSave()));


}
void ShortestPathWindow::onActionOpen(){
    shortestpath->clearState();
    QTextCodec *codec=QTextCodec::codecForName("utf-8");
    QString filter=codec->toUnicode("最短路径文件(*.stp)");
    QString fileName=QFileDialog::getOpenFileName(
                this,"打开文件",QString(),filter);
    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly))
        {
            int tempint;
            double tempdouble;
            bool tempbool;
            file.read((char*)&tempint,sizeof(int));
            shortestpath->setWinOffsetX(tempint);
            file.read((char*)&tempint,sizeof(int));
            shortestpath->setWinOffsetY(tempint);
            file.read((char*)&tempdouble,sizeof(double));
            shortestpath->setWinScale(tempdouble);
            Graph* g=shortestpath->getGraph();
            g->clearVertexs();
            int vertexcount;
            file.read((char*)&vertexcount,sizeof(int));
            for(int i=1;i<=vertexcount;i++){
                Vertex* v=new Vertex();
                file.read((char*)&tempint,sizeof(int));
                v->setCenterX(tempint);
                file.read((char*)&tempint,sizeof(int));
                v->setCenterY(tempint);
                int paramcount;
                file.read((char*)&paramcount,sizeof(int));
                for(int j=0;j<paramcount;j++){
                    VertexParam* vp=new VertexParam();
                    file.read((char*)&tempint,sizeof(int));
                    vp->setX(tempint);
                    file.read((char*)&tempint,sizeof(int));
                    vp->setY(tempint);
                    file.read((char*)&tempdouble,sizeof(double));
                    vp->setDeg(tempdouble);
                    file.read((char*)&tempdouble,sizeof(double));
                    vp->setDis(tempdouble);
                    file.read((char*)&tempbool,sizeof(bool));
                    vp->setCurve(tempbool);
                    file.read((char*)&tempint,sizeof(int));
                    vp->setP(tempint);
                    file.read((char*)&tempint,sizeof(int));
                    vp->setE(tempint);
                    v->addVertexParams(vp);

                }
                g->addVertex(v);
            }
            shortestpath->saveWinOffset();
            ui->rbEditMode->setChecked(true);
            update();
        }

    }
}
void ShortestPathWindow::onActionSave(){
    shortestpath->clearState();
    QTextCodec *codec=QTextCodec::codecForName("utf-8");
    QString filter=codec->toUnicode("最短路径文件(*.stp)");
    QString fileName=QFileDialog::getSaveFileName(
                this,"保存文件",QString(),filter);
    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly))
        {
            int tempint;
            double tempdouble;
            bool tempbool;
            tempint=shortestpath->getWinOffsetX();
            file.write((char*)&tempint,sizeof(int));
            tempint=shortestpath->getWinOffsetY();
            file.write((char*)&tempint,sizeof(int));
            tempdouble=shortestpath->getWinScale();
            file.write((char*)&tempdouble,sizeof(double));
            Graph* g=shortestpath->getGraph();
            tempint=g->getCount();
            file.write((char*)&tempint,sizeof(int));
            for(int i=1;i<=g->getCount();i++){
                Vertex* v=g->getVertexAt(i);
                tempint=v->getCenterX();
                file.write((char*)&tempint,sizeof(int));
                tempint=v->getCenterY();
                file.write((char*)&tempint,sizeof(int));
                tempint=v->getParams()->count();
                file.write((char*)&tempint,sizeof(int));
                for(int j=0;j<v->getParams()->count();j++){
                    VertexParam* vp=v->getParams()->at(j);
                    tempint=vp->getX();
                    file.write((char*)&tempint,sizeof(int));
                    tempint=vp->getY();
                    file.write((char*)&tempint,sizeof(int));
                    tempdouble=vp->getDeg();
                    file.write((char*)&tempdouble,sizeof(double));
                    tempdouble=vp->getDis();
                    file.write((char*)&tempdouble,sizeof(double));
                    tempbool=vp->getCurve();
                    file.write((char*)&tempbool,sizeof(bool));
                    tempint=vp->getP();
                    file.write((char*)&tempint,sizeof(int));
                    tempint=vp->getE();
                    file.write((char*)&tempint,sizeof(int));

                }
            }
            QMessageBox::information(this,"提示","保存成功",QMessageBox::Ok);
        }

    }


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
    if(QMessageBox::Yes==QMessageBox::warning(this,"警告","是否全部删除?",QMessageBox::Yes,QMessageBox::No))
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
        ui->rbEditMode->setEnabled(false);
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
    ui->rbEditMode->setEnabled(true);
    int i=ui->cbMethod->currentIndex();
    if(i==0){
        shortestpath->setMethod(DisplayFrame::Bellman);
        shortestpath->getGraph()->bellman();   
        QStringList list=shortestpath->getGraph()->getCalcResult();
        ui->tbDetail->setText(list.join("\n"));
    }else if(i==1){
        shortestpath->setMethod(DisplayFrame::Floyd);
        shortestpath->getGraph()->floyd();
        QStringList list=shortestpath->getGraph()->getCalcResult();
        ui->tbDetail->setText(list.join("\n"));
    }

}
