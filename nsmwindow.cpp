#include "nsmwindow.h"
#include "ui_nsmwindow.h"
#include "launchdialog.h"
#include "setdemanddialog.h"
#include <QScreen>
#include <QMessageBox>
#include <QTextCodeC>
#include <QFileDialog>
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
    event->accept();
}

QWidget *NSMWindow::parent() const
{
    return mParent;
}
NSMWindow::~NSMWindow()
{
    delete ui;
    if(oriGraphData!=NULL){
       delete oriGraphData;
    }

}
void NSMWindow::init(){
    nsm=ui->nsm;
    oriGraphData=NULL;
    connect(ui->btnAddVertex,SIGNAL(clicked()),this,SLOT(onBtnAddVertexClicked()));
    connect(ui->btnRemoveAllVertex,SIGNAL(clicked()),this,SLOT(onBtnRemoveAllVertexClicked()));
    connect(ui->rbEditMode,SIGNAL(toggled(bool)),this,SLOT(onRadioBtnEditModeToggled(bool)));
    connect(ui->btnCalculate,SIGNAL(clicked()),this,SLOT(onBtnCalcClicked()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(onActionOpen()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(onActionSave()));

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
        nsm->moveVertexLabel(v);
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
    if(nsm->getEditable()){
        saveOriGraphData();
    }
    ui->rbEditMode->setChecked(false);
    loadOriGraphData();
    if(ERROR_CODE!=nsm->getGraph()->ctsma()){
        QList<NSMGraphData*>* data=nsm->getGraph()->getGraphData();
        ui->cbStep->clear();
        for(int i=1;i<=data->count();i++){
            ui->cbStep->addItem(QString::number(i));
        }
        ui->cbStep->setCurrentIndex(ui->cbStep->count()-1);
    }else{

    }
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
        loadOriGraphData();
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
void NSMWindow::onActionOpen(){
    nsm->clearState();
    QTextCodec *codec=QTextCodec::codecForName("utf-8");
    QString filter=codec->toUnicode("网络单纯形法文件(*.nsm)");
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
            nsm->setWinOffsetX(tempint);
            file.read((char*)&tempint,sizeof(int));
            nsm->setWinOffsetY(tempint);
            file.read((char*)&tempdouble,sizeof(double));
            nsm->setWinScale(tempdouble);
            NSMGraph* g=nsm->getGraph();
            g->clearVertexs();
            int vertexcount;
            file.read((char*)&vertexcount,sizeof(int));
            for(int i=1;i<=vertexcount;i++){
                NSMVertex* v=new NSMVertex();
                file.read((char*)&tempint,sizeof(int));
                v->setB(tempint);
                file.read((char*)&tempint,sizeof(int));
                v->setPi(tempint);
                file.read((char*)&tempint,sizeof(int));
                v->setBCenterX(tempint);
                file.read((char*)&tempint,sizeof(int));
                v->setBCenterY(tempint);
                file.read((char*)&tempint,sizeof(int));
                v->setBWidth(tempint);
                file.read((char*)&tempint,sizeof(int));
                v->setPiCenterX(tempint);
                file.read((char*)&tempint,sizeof(int));
                v->setPiCenterY(tempint);
                file.read((char*)&tempint,sizeof(int));
                v->setPiWidth(tempint);
                file.read((char*)&tempint,sizeof(int));
                v->setLabelPos(tempint);
                file.read((char*)&tempint,sizeof(int));
                v->setCenterX(tempint);
                file.read((char*)&tempint,sizeof(int));
                v->setCenterY(tempint);
                int paramcount;
                file.read((char*)&paramcount,sizeof(int));
                for(int j=0;j<paramcount;j++){

                    NSMVertexParam* vp=new NSMVertexParam();
                    file.read((char*)&tempint,sizeof(int));
                    vp->setCost(tempint);
                    file.read((char*)&tempint,sizeof(int));
                    vp->setFlow(tempint);
                    file.read((char*)&tempint,sizeof(int));
                    vp->setCapacity(tempint);
                    file.read((char*)&tempint,sizeof(int));
                    vp->setCX(tempint);
                    file.read((char*)&tempint,sizeof(int));
                    vp->setCY(tempint);
                    file.read((char*)&tempint,sizeof(int));
                    vp->setCWidth(tempint);
                    file.read((char*)&tempdouble,sizeof(double));
                    vp->setCDeg(tempdouble);
                    file.read((char*)&tempdouble,sizeof(double));
                    vp->setCDis(tempdouble);
                    file.read((char*)&tempint,sizeof(int));
                    vp->setFX(tempint);
                    file.read((char*)&tempint,sizeof(int));
                    vp->setFY(tempint);
                    file.read((char*)&tempint,sizeof(int));
                    vp->setFWidth(tempint);
                    file.read((char*)&tempdouble,sizeof(double));
                    vp->setFDeg(tempdouble);
                    file.read((char*)&tempdouble,sizeof(double));
                    vp->setFDis(tempdouble);
                    file.read((char*)&tempbool,sizeof(bool));
                    vp->setCurve(tempbool);
                    file.read((char*)&tempint,sizeof(int));
                    vp->setP(tempint);
                    v->addVertexParams(vp);


                }

                g->addVertex(v);
                v->saveBCenter();
                v->saveCenter();
                v->savePiCenter();
                nsm->moveVertexLabel(v);

            }
            nsm->saveWinOffset();
            ui->rbEditMode->setChecked(true);
            update();
        }

    }
}
void NSMWindow::onActionSave(){
    nsm->clearState();
    QTextCodec *codec=QTextCodec::codecForName("utf-8");
    QString filter=codec->toUnicode("网络单纯形法文件(*.nsm)");
    QString fileName=QFileDialog::getSaveFileName(
                this,"保存文件",QString(),filter);
    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly))
        {
            int tempint;
            double tempdouble;
            bool tempbool;
            tempint=nsm->getWinOffsetX();
            file.write((char*)&tempint,sizeof(int));
            tempint=nsm->getWinOffsetY();
            file.write((char*)&tempint,sizeof(int));
            tempdouble=nsm->getWinScale();
            file.write((char*)&tempdouble,sizeof(double));
            NSMGraph* g=nsm->getGraph();
            tempint=g->getCount();
            file.write((char*)&tempint,sizeof(int));
            for(int i=1;i<=g->getCount();i++){
                NSMVertex* v=g->getVertexAt(i);
                tempint=v->getB();
                file.write((char*)&tempint,sizeof(int));
                tempint=v->getPi();
                file.write((char*)&tempint,sizeof(int));
                tempint=v->getBCenterX();
                file.write((char*)&tempint,sizeof(int));
                tempint=v->getBCenterY();
                file.write((char*)&tempint,sizeof(int));
                tempint=v->getBWidth();
                file.write((char*)&tempint,sizeof(int));
                tempint=v->getPiCenterX();
                file.write((char*)&tempint,sizeof(int));
                tempint=v->getPiCenterY();
                file.write((char*)&tempint,sizeof(int));
                tempint=v->getPiWidth();
                file.write((char*)&tempint,sizeof(int));
                tempint=v->getLabelPos();
                file.write((char*)&tempint,sizeof(int));
                tempint=v->getCenterX();
                file.write((char*)&tempint,sizeof(int));
                tempint=v->getCenterY();
                file.write((char*)&tempint,sizeof(int));
                tempint=v->getParams()->count();
                file.write((char*)&tempint,sizeof(int));
                for(int j=0;j<v->getParams()->count();j++){
                    NSMVertexParam* vp=v->getParams()->at(j);
                    tempint=vp->getCost();
                    file.write((char*)&tempint,sizeof(int));
                    tempint=vp->getFlow();
                    file.write((char*)&tempint,sizeof(int));
                    tempint=vp->getCapacity();
                    file.write((char*)&tempint,sizeof(int));
                    tempint=vp->getCX();
                    file.write((char*)&tempint,sizeof(int));
                    tempint=vp->getCY();
                    file.write((char*)&tempint,sizeof(int));
                    tempint=vp->getCWidth();
                    file.write((char*)&tempint,sizeof(int));
                    tempdouble=vp->getCDeg();
                    file.write((char*)&tempdouble,sizeof(double));
                    tempdouble=vp->getCDis();
                    file.write((char*)&tempdouble,sizeof(double));
                    tempint=vp->getFX();
                    file.write((char*)&tempint,sizeof(int));
                    tempint=vp->getFY();
                    file.write((char*)&tempint,sizeof(int));
                    tempint=vp->getFWidth();
                    file.write((char*)&tempint,sizeof(int));
                    tempdouble=vp->getFDeg();
                    file.write((char*)&tempdouble,sizeof(double));
                    tempdouble=vp->getFDis();
                    file.write((char*)&tempdouble,sizeof(double));
                    tempbool=vp->getCurve();
                    file.write((char*)&tempbool,sizeof(bool));
                    tempint=vp->getP();
                    file.write((char*)&tempint,sizeof(int));


                }
            }
            QMessageBox::information(this,"提示","保存成功",QMessageBox::Ok);
        }

    }


}
void NSMWindow::saveOriGraphData(){
    NSMGraph* graph=nsm->getGraph();
    if(oriGraphData!=NULL){
        delete oriGraphData;
    }
    oriGraphData=new NSMGraphData(0);
    for(int i=1;i<=graph->getCount();i++){
        NSMVertex* v=graph->getVertexAt(i);
        NSMVertexData* vd=new NSMVertexData();
        vd->setB(v->getB());
        vd->setPi(v->getPi());
        for(int j=0;j<v->getParams()->count();j++){
            NSMVertexParam* p=v->getParams()->at(j);
            NSMVertexParamData* pd=new NSMVertexParamData();
            pd->setC(p->getC());
            pd->setCapacity(p->getCapacity());
            pd->setCost(p->getCost());
            pd->setFlow(p->getFlow());
            pd->setP(p->getP());
            pd->setRc(p->getRc());
            vd->getParams()->append(pd);

        }
        oriGraphData->getVertexDatas()->append(vd);

    }


}
void NSMWindow::loadOriGraphData(){
    NSMGraph* graph=nsm->getGraph();
    if(oriGraphData!=NULL){
        for(int i=1;i<=graph->getCount();i++){
            NSMVertex* v=graph->getVertexAt(i);
            NSMVertexData* vd=oriGraphData->getVertexDatas()->at(i-1);
            v->setB(vd->getB());
            v->setPi(vd->getPi());
            for(int j=0;j<v->getParams()->count();j++){
                NSMVertexParam* p=v->getParams()->at(j);
                NSMVertexParamData* pd=vd->getParams()->at(j);
                p->setC(pd->getC());
                p->setCapacity(pd->getCapacity());
                p->setCost(pd->getCost());
                p->setFlow(pd->getFlow());
                p->setP(pd->getP());
                p->setRc(pd->getRc());
            }


        }
    }


}


