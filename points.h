#ifndef POINTS_H
#define POINTS_H
#include <QVector>
#include <QThread>

class Points: public QThread{
    Q_OBJECT
public:
    explicit Points(QObject* parent = 0);
    virtual ~Points();    
    void changeFieldType(int n);
    void setNumberOfCells(int n);
    void setPoints(const QVector<QPair<int, int>> *p);
    void setRange(int start, int finish);
    void clearNewPoints();
    QVector<QPair<int, int>> &getNewPoints();

public slots:
    void run();

signals:

//private:
protected:
    void findPotentialPoints();
    void findNewPoints();
    QVector<QPair<int, int>> findNeighbors(int X, int Y) const;
    unsigned short countPointsAround(const QVector<QPair<int, int> > &neighbors_) const;
    unsigned short countPointsAroundAndAddPotentialPoints(const QVector<QPair<int,int>> &neighbors_);
    void addToPotentialPoints(QPair<int, int> neighbour);
    bool pointOnField(const QVector<QPair<int,int>>::const_iterator itP) const;
    bool pointsConsist(QPair<int,int> neighbour) const;
    const QVector<QPair<int,int>> *points;
    QVector<QPair<int,int>> potentialPoints;
    QVector<QPair<int,int>> newPoints;
    int begin;
    int end;
    int numberOfCells;
    bool endlessField;
};

#endif // POINTS_H

