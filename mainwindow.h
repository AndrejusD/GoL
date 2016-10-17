#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customscene.h"
#include "points.h"
#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPair>
#include <QThread>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    //int  recountCoordinates(int ,char );

private slots:
    void on_mousePressedEvent(QGraphicsSceneMouseEvent *event);
    void on_pushButtonStart_clicked();
    void on_pushButtonStop_clicked();
    void on_timeout();
    void on_lineEdit_editingFinished();
    void on_pushButtonResetCounter_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_checkBox_stateChanged(int arg1);
    void on_pushButtonClearField_clicked();
    void on_pushButtonAddCells_clicked();
    void paint();
    void on_checkBoxThreads_stateChanged(int arg1);

    void on_pushButtonStep_clicked();

signals:

private:
    void resizeEvent(QResizeEvent* e);
    int  recountCoordinates(int ,char );
    void setThreads();
    void setLimitsAndStartThreads();
    void waitThreads();
    void collectNewPoints();
    void sortPoints();
    void drawField();
    void clearField();
    void writeToFile();
    Ui::MainWindow *ui;
    CustomScene *scene;
    QGraphicsLineItem *line[4];
    const QBrush brush = Qt::green;
    const QPen pen = Qt::NoPen;
    QTimer *timer;
    QVector<Points*> threads;
    QVector<QPair<int,int>> points_;
    const int mapTX = -3; // map coordinates corection -3
    const int mapTY = -4;
    const int boarders = 4;
    int fieldSize;
    int counter;
    int speed;
    int Xmin;
    int Xmax;
    int Ymin;
    int Ymax;
    int numberOfThreads;
};

#endif // MAINWINDOW_H
