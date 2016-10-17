#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QRegExpValidator>
#include <QTime>
#include <QScrollBar>
//#include <QGLWidget>
#include <QMessageBox>
#include <QFile>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new CustomScene(this);

    QRegExp exp("[0-9]{1,8}");
    ui->lineEdit->setValidator(new QRegExpValidator(exp,this));

    ui->graphicsView->setScene(scene);
    connect(scene,SIGNAL(mousePressed(QGraphicsSceneMouseEvent*)),
            this,SLOT(on_mousePressedEvent(QGraphicsSceneMouseEvent*)));

    timer = new QTimer(this);
    speed = 300/ui->horizontalSlider->value();
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeout()));        
    on_pushButtonResetCounter_clicked();    

    connect(ui->graphicsView->horizontalScrollBar(),SIGNAL(valueChanged(int)),this ,SLOT(paint()));
    connect(ui->graphicsView->verticalScrollBar(),SIGNAL(valueChanged(int)),this ,SLOT(paint()));

    //ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers| QGL::DirectRendering)));
    //ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    setThreads();
    on_lineEdit_editingFinished();
    for(int i=0; i<boarders; i++)
        line[i] = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;    
}

void MainWindow::on_mousePressedEvent(QGraphicsSceneMouseEvent *event)
{
    int X = recountCoordinates(event->scenePos().x(), 'X');
    int Y = recountCoordinates(event->scenePos().y(), 'Y');

    auto XY = qMakePair(X/8,Y/8);

    if(QGraphicsItem *item = scene->itemAt( event->scenePos(), QTransform())){
        if(item->type() == 3){                          //checks if line (border) not clicked
             scene->removeItem(item);
             points_.removeAll(XY);
        }
    }
    else{
        scene->addRect(X + mapTX, Y + mapTY, 7, 7, pen, Qt::green);        
        auto it = qLowerBound(points_.begin(),points_.end(), XY);
        points_.insert(it,XY);
    }
    ui->label_numberOfPoints->setText(QString::number(points_.size()));
}

void MainWindow::on_pushButtonStart_clicked()
{
    if(points_.empty()){
        QMessageBox::information(0, "Information",
                                 "There are no points for 'life'. Please add points.");
        return;
    }
    timer->start(speed);
    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonClearField->setEnabled(false);
    ui->pushButtonResetCounter->setEnabled(false);    
    ui->pushButtonAddCells->setEnabled(false);
    ui->pushButtonStep->setEnabled(false);
    ui->pushButtonStop->setEnabled(true);
}

void MainWindow::on_pushButtonStop_clicked()
{
    timer->stop();
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonClearField->setEnabled(true);
    ui->pushButtonResetCounter->setEnabled(true);        
    ui->pushButtonAddCells->setEnabled(true);
    ui->pushButtonStep->setEnabled(true);
    ui->pushButtonStart->setEnabled(true);
}

void MainWindow::on_timeout()
{
    if(points_.empty()){
        on_pushButtonStop_clicked();
        return;
    }
    //if(counter<151) writeToFile();

    QTime t;
    t.start();

    setLimitsAndStartThreads();
    waitThreads();
    points_.clear();
    collectNewPoints();
    sortPoints();

    counter++;
    ui->statusBar->showMessage("Counter : "+QString::number(counter));
    ui->lcdNumber->display(t.elapsed());
    ui->dial->setValue(t.elapsed());

    //qDebug("Calculation: %d ms", t.elapsed());
    paint();
}

void MainWindow::on_pushButtonResetCounter_clicked()
{
    counter = 0;
    ui->statusBar->showMessage("Counter : "+QString::number(counter));
}

void MainWindow::on_lineEdit_editingFinished()
{
    fieldSize = ui->lineEdit->text().toInt();
    int numberOfCells = fieldSize/2;
    fieldSize = fieldSize * 4 + 6;
    ui->graphicsView->setSceneRect(-fieldSize - 20,-fieldSize - 20,fieldSize*2 + 40,fieldSize*2 + 40);
    for(int i=0; i<numberOfThreads; i++)
        threads[i]->setNumberOfCells(numberOfCells);
    paint();
}

void MainWindow::setThreads()
{
    numberOfThreads = QThread::idealThreadCount();
    for(int i=0; i<numberOfThreads; i++){
        Points *P = new Points(this);
        threads.append(P);
        try{
            threads[i]->setPoints(&points_);
        }catch(...){
            QMessageBox::critical(0,"Critical", "Attempt to access an uninitialized pointer \n in function setTreads()");
        }
        connect(this,SIGNAL(destroyed()),threads[i],SLOT(quit()));
    }
}

void MainWindow::setLimitsAndStartThreads()
{
    int endPoint = -1;
    int lastPoint = points_.size() - 1;
    for(int i=0; i<numberOfThreads; i++){
        int startPoint = endPoint + 1;
        endPoint = ((i+1)* lastPoint) / numberOfThreads;
        threads[i]->setRange(startPoint, endPoint);        
        threads[i]->start();
    }
}

void MainWindow::waitThreads()
{
    for(int i=0; i<numberOfThreads; i++)
        threads[i]->wait();
}

void MainWindow::collectNewPoints()
{
    for(int i=0; i<numberOfThreads; i++){
        points_.append(threads[i]->getNewPoints());
        threads[i]->clearNewPoints();
    }
}

void MainWindow::sortPoints() // and remove duplicates
{
    qSort(points_);
    auto itP = points_.begin();
    if(itP == points_.end()) return;
    auto itNext = itP++;
    while(itP != points_.end()){
        if (*itNext == *itP)
            itP = points_.erase(itP);
        else
            itNext = itP++;
    }
}

void MainWindow::drawField()
{
    QPen linePen(Qt::red);
    if(ui->checkBox->isChecked()){
        QPen lPen(Qt::blue);
        linePen = lPen;
    }
    linePen.setWidth(2);
    line[0] = scene->addLine(-fieldSize+2,-fieldSize-1,fieldSize,-fieldSize-1,linePen);//upper
    line[1] = scene->addLine(-fieldSize+1,-fieldSize,-fieldSize+1,fieldSize-1,linePen);//left
    line[2] = scene->addLine(-fieldSize+1,fieldSize,fieldSize,fieldSize,linePen);//bottom
    line[3] = scene->addLine(fieldSize+1,-fieldSize,fieldSize+1,fieldSize-1,linePen);//right
}

void MainWindow::clearField()
{
    scene->clear();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    speed = 300/value;
    timer->setInterval(speed);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    for(int i=0; i<4; i++){
        if(line[i] != NULL)
        scene->removeItem(line[i]);
        line[i] = NULL;
    }
    drawField();
    for(int i=0; i<numberOfThreads; i++)
        threads[i]->changeFieldType(arg1);
}

void MainWindow::on_pushButtonClearField_clicked()
{
    clearField();
    points_.clear();
    drawField();
    ui->label_numberOfPoints->setText(QString::number(points_.size()));
}

void MainWindow::on_pushButtonAddCells_clicked()
{
    //QTime t;
    //t.start();
    const int S = fieldSize/10;// Amount of starting points = [(S*2)*(S*2)]

    QVector<QPair<int,int>> newPoints;
    for(int i(0); i<S; i++){
        for(int j(0); j<S; j++){
            int X = i*2 - (S-1);
            int Y = j*2 - (S-1);
            newPoints.append(qMakePair(X,Y));
        }
    }
    for(int i(0); i<(S+1); i++){
        for(int j(0); j<(S+1); j++){
            int X = i*2 - S;
            int Y = j*2 - S;            
            newPoints.append(qMakePair(X,Y));
        }
    }
    points_ += newPoints;
    ui->label_numberOfPoints->setText(QString::number(points_.size()));
    qSort(points_);
    //qDebug("Add2: %d ms", t.elapsed());
    paint();
}

void MainWindow::paint()
{
    //QTime t;
    //t.start();

    clearField();
    drawField();

        QPolygonF P = ui->graphicsView->mapToScene(QRect(0, 0,
                                                         ui->graphicsView->viewport()->width(),
                                                         ui->graphicsView->viewport()->height()));
        int Xmin = (P[0].rx()-10)/8;
        int Ymin = (P[0].ry()-10)/8;
        int Xmax = (P[2].rx()+10)/8;
        int Ymax = (P[2].ry()+10)/8;
        auto begin = qMakePair(Xmin,Ymin);
        auto  end  = qMakePair(Xmax,Ymax);

        auto itBegin = qLowerBound(points_.constBegin(),points_.constEnd(), begin);
        auto  itEnd  = qLowerBound(points_.constBegin(),points_.constEnd(), end);

        while(itBegin != itEnd){
            int Y = itBegin->second;
            if( (Y>Ymin)&&(Y<Ymax) ){
                int X = itBegin->first;
                scene->addRect(X*8 + mapTX, Y*8 + mapTY, 7, 7, pen, Qt::green);
            }
            itBegin++;
        }    
    ui->label_numberOfPoints->setText(QString::number(points_.size()));
    //qDebug("Paint: %d ms", t.elapsed());
}

void MainWindow::on_checkBoxThreads_stateChanged(int arg1)
{
    if(arg1)
        numberOfThreads = QThread::idealThreadCount();
    else
        numberOfThreads = 1;

}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    paint();
    Q_UNUSED(e);
}

int MainWindow::recountCoordinates(int Z, char C)
{
    (C == 'X') ? Z-=mapTX : Z-=mapTY;// coordinates ajustment for mouse and maps
    int z = Z % 8;
    (Z < 0) ? Z-=(z + 8) : Z-=z;
    return Z;
}


void MainWindow::on_pushButtonStep_clicked()
{
    on_timeout();
}

//**********************************************************************************
void MainWindow::writeToFile()
{
    QFile file("../Expected_data.txt");
    QTextStream out(&file);
    if(file.open(QIODevice::Append))
    {
        out<<QString::number(counter)<<endl;
        out<<QString::number(points_.size())<<endl;
        foreach (auto p, points_) {
            out << QString::number(p.first)<<":"<<QString::number(p.second)<<endl;}
    }
    file.close();
}
