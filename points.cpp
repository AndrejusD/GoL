#include "points.h"
//#include <QDebug>
//#include <iterator>

Points::Points(QObject *parent) :
    QThread(parent),
    endlessField (true)
{

}

Points::~Points()
{

}

void Points::run()
{
    findPotentialPoints();
    findNewPoints();
}

void Points::findPotentialPoints()
{
    auto itP = points->constBegin()+begin;
    for( ; itP != points->constBegin()+end; itP++){
        if(pointOnField(itP)) {
            auto neighbors =  findNeighbors(itP->first, itP->second);
            auto numberOfPointsArround = countPointsAroundAndAddPotentialPoints(neighbors);
            if( (numberOfPointsArround == 2)||(numberOfPointsArround == 3) )
                newPoints.append(*itP);
        }
    }
}

void Points::findNewPoints()
{
    foreach(const auto pPoint, potentialPoints) {
        auto neighbors = findNeighbors(pPoint.first, pPoint.second);
        auto numberOfPointsArround = countPointsAround(neighbors);
        if(numberOfPointsArround == 3)   newPoints.append(pPoint);
    }
    potentialPoints.clear();
}

QVector<QPair<int, int>> Points::findNeighbors(int X, int Y) const
{
    int left, right, upper, bottom;
    bool L=0, R=0, U=0, B=0;

    if(X-1 < -numberOfCells)
        left = numberOfCells;
    else
        left = X-1, L = 1;

    if(X+1 >  numberOfCells)
        right = -numberOfCells;
    else
        right = X+1, R = 1;

    if(Y-1 < -numberOfCells)
        upper = numberOfCells;
    else
        upper = Y-1, U = 1;

    if(Y+1 >  numberOfCells)
        bottom = -numberOfCells;
    else
        bottom = Y+1, B =1;

    QVector<QPair<int, int>> neighbors;
    if(endlessField || (L && U) )
        neighbors.push_back(qMakePair(left ,upper ));
    if(endlessField || (L     ) )
        neighbors.push_back(qMakePair(left ,   Y  ));
    if(endlessField || (L && B) )
        neighbors.push_back(qMakePair(left ,bottom));
    if(endlessField || (     U) )
        neighbors.push_back(qMakePair( X   ,upper ));
    if(endlessField || (     B) )
        neighbors.push_back(qMakePair( X   ,bottom));
    if(endlessField || (R && U) )
        neighbors.push_back(qMakePair(right,upper ));
    if(endlessField || (R     ) )
        neighbors.push_back(qMakePair(right,  Y   ));
    if(endlessField || (R && B) )
        neighbors.push_back(qMakePair(right,bottom));
    return neighbors;
}

unsigned short Points::countPointsAround(const QVector<QPair<int, int> > &neighbors_) const
{
    unsigned short numberOfPointsArround = 0;
    foreach ( auto neighbour, neighbors_) {
        if( pointsConsist(neighbour))
            numberOfPointsArround++;
    }
    return numberOfPointsArround;
}

unsigned short Points::countPointsAroundAndAddPotentialPoints(const QVector<QPair<int, int> > &neighbours)
{
    unsigned short numberOfPointsArround = 0;
    foreach (const auto neighbour, neighbours) {
        if( pointsConsist(neighbour))
            numberOfPointsArround++;
        else
            addToPotentialPoints(neighbour);
    }
    return numberOfPointsArround;
}

void Points::addToPotentialPoints(QPair<int, int> neighbour)
{
    auto itP = qLowerBound( potentialPoints.begin(), potentialPoints.end(), neighbour);
    if ((neighbour != *itP)||(itP == potentialPoints.end()))
        potentialPoints.insert(itP,neighbour);
}

bool Points::pointOnField(const QVector<QPair<int,int>>::const_iterator itP) const
{
    if(abs(itP->first ) > numberOfCells) return false;
    if(abs(itP->second) > numberOfCells) return false;
    return true;
}

bool Points::pointsConsist(QPair<int,int> neighbour) const
{
    if(qBinaryFind( points->constBegin(),points->constEnd(), neighbour) == points->constEnd())
        return false;
    else
        return true;
}

void Points::changeFieldType(int n)
{
    if(n)
        endlessField = true;
    else
        endlessField = false;
}

void Points::setNumberOfCells(int n)
{
    numberOfCells = n;
}

void Points::setPoints(const QVector<QPair<int,int>> *p)
{
    if(p == NULL)
        throw 1;
    else
        points = p;
}

void Points::setRange(int start, int finish)
{
    begin = start;
    end = finish+1;
}

void Points::clearNewPoints()
{
    newPoints.clear();
}

QVector<QPair<int, int>> &Points::getNewPoints()
{
    return newPoints;
}




