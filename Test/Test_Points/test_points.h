#ifndef TEST_GOL_H
#define TEST_GOL_H
#include <QtTest>
#include "../../points.h"

class Test_GOL_Points :  public Points
{
    Q_OBJECT

public:
    Test_GOL_Points();

private Q_SLOTS:
    void test_changeFieldType();
    void test_setNumberOfCells();
    void test_setPoints();
    void test_setRange();
    void test_clearNewPoints();
    void test_getNewPoints();
    void test_run();

    void test_findPotentialPoints();
    void test_findNewPoints();
    void test_findNeighbours();
    void test_countPointsAround();
    void test_countPointsAroundAndAddPotentialPoints();
    void test_addToPotentialPoints();
    void test_pointIsOutOfField();
    void test_pointsConsist();

private:

};

#endif // TEST_GOL_H
