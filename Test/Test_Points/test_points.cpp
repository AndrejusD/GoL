#include "test_points.h"

Test_GOL_Points::Test_GOL_Points()
{
}

void Test_GOL_Points::test_changeFieldType()
{
    bool actual, expected = true;
    for(int i= -3; i<4; i++){
        changeFieldType(i);
        actual = endlessField;
        if(i)
            QVERIFY2(actual == expected ,QTest::toString("Error at i = "  + QString::number(i)));
        else
            QVERIFY2(actual != expected ,QTest::toString("Error at i = "  + QString::number(i)));
    }
}

void Test_GOL_Points::test_setNumberOfCells()
{
    int actual, expected = 100;
    for(int i=0; i<10; i++){
        actual = 0;
        expected += i*100;
        setNumberOfCells(expected);
        actual = numberOfCells;
        QVERIFY2(actual == expected ,QTest::toString("Error at i = "  + QString::number(i)));
    }
}

void Test_GOL_Points::test_setPoints()
{
    QVector<QPair<int,int>> *p = NULL;
    QVERIFY_EXCEPTION_THROWN(setPoints(p), int);

    QVector<QPair<int,int>> test;
    test.append(qMakePair( 10, 20));
    test.append(qMakePair( 30, 40));
    test.append(qMakePair(-50,-60));
    test.append(qMakePair(-70,-80));
    p = &test;
    setPoints(p);
    QCOMPARE(points->at(0).first ,  10);
    QCOMPARE(points->at(1).second,  40);
    QCOMPARE(points->at(2).first , -50);
    QCOMPARE(points->at(3).second, -80);
}

void Test_GOL_Points::test_setRange()
{
    int actualBegin, actualEnd,
        expectedBegin, expectedEnd;
    for(int i=0; i<10; i++){
        expectedBegin = i*100;
        expectedEnd   = expectedBegin + 99;
        setRange(expectedBegin,expectedEnd);
        actualBegin = begin;
        actualEnd   = end - 1;
        QCOMPARE(actualBegin,expectedBegin);
        QCOMPARE(actualEnd,expectedEnd);
    }
}

void Test_GOL_Points::test_clearNewPoints()
{
    for(int i=0,j=9; i<100; i++,j++)
        newPoints.append(qMakePair(i,j));
    QCOMPARE(newPoints.size(),100);
    QEXPECT_FAIL("", "OK_1 - designful error", Continue);
    QVERIFY(newPoints.empty());
    clearNewPoints();
    QVERIFY(newPoints.empty());
}

void Test_GOL_Points::test_getNewPoints()
{
    for(int i=0,j=9; i<100; i++,j++)
        newPoints.append(qMakePair(i,j));
    QVector<QPair<int,int>> points;
    points.append(getNewPoints());
    for(int i=0; i<100; i++)
        QCOMPARE(points.at(i),newPoints.at(i));
    QCOMPARE(points.size(),newPoints.size());
    clearNewPoints();
}

void Test_GOL_Points::test_run()
{
    Test_GOL_Points P;
    P.setNumberOfCells(25);
    P.changeFieldType(0);
    QVector<QPair<int,int>> points;
    const int S = 20;
    for(int i(0); i<S; i++){
        for(int j(0); j<S; j++){
            int X = i*2 - (S-1);
            int Y = j*2 - (S-1);
            points.append(qMakePair(X,Y));
        }
    }
    for(int i(0); i<(S+1); i++){
        for(int j(0); j<(S+1); j++){
            int X = i*2 - S;
            int Y = j*2 - S;
            points.append(qMakePair(X,Y));
        }
    }
    P.setPoints(&points);
    QFile file1("../../Actual_data.txt");
    file1.remove();
    QFile file2("../../Expected_data.txt");
    for(int i=0; i<151; i++){
        qSort(points);
        QTextStream out(&file1);
        if(file1.open(QIODevice::Append))        {
            out<<QString::number(i)<<endl;
            out<<QString::number(points.size())<<endl;
            foreach (auto p, points) {
                out << QString::number(p.first)<<":"<<QString::number(p.second)<<endl;}
        }
        else{
            //qDebug() << "File Actual_data.txt writing error."<<endl;
            QVERIFY2(false, "Failure testing run(). File Actual_data.txt writing error.");
        }
        file1.close();
        P.setRange( 0, points.size() - 1);
        P.run();
        points.clear();
        points.append(P.getNewPoints());
        P.clearNewPoints();
    }
    if (!file1.open(QIODevice::ReadOnly)) {
        //qDebug() << "File Actual_data.txt open error."<<endl;
        QVERIFY2(false, "Failure testing run(). File Actual_data.txt open error.");
        return;
    }
    if (!file2.open(QIODevice::ReadOnly)) {
        //qDebug() << "File Expected_data open error."<<endl;
        QVERIFY2(false, "Failure testing run(). File Expected_data.txt open error.");
        return;
    }
    QTextStream in1(&file1);
    QString wholeFile1 = in1.readAll();
    QTextStream in2(&file2);
    QString wholeFile2 = in2.readAll();
    file1.close();
    file2.close();
    //file1.remove();
    QCOMPARE(wholeFile1,wholeFile2);
}

void Test_GOL_Points::test_findPotentialPoints()
{
    QVector<QPair<int,int>> t_points;
    numberOfCells = 10;
    t_points.clear();
    t_points.append(qMakePair(-1,-1));
    t_points.append(qMakePair( 0, 0));
    t_points.append(qMakePair( 1, 1));
    begin = 0;
    end = 3;
    qSort(t_points);
    setPoints(&t_points);
    potentialPoints.clear();

    QCOMPARE( potentialPoints.size(), 0);
    findPotentialPoints();
    qSort(potentialPoints);
    QCOMPARE(potentialPoints.size(), 16);
    QCOMPARE(potentialPoints[0] ,qMakePair(-2,-2));
    QCOMPARE(potentialPoints[5] ,qMakePair(-1, 1));
    QCOMPARE(potentialPoints[13],qMakePair( 2, 0));
    QCOMPARE(potentialPoints[15],qMakePair( 2, 2));

}

void Test_GOL_Points::test_findNewPoints()
{
    QVector<QPair<int,int>> t_points;
    numberOfCells = 10;
    t_points.append(qMakePair( 0, 1));
    t_points.append(qMakePair( 1, 2));
    t_points.append(qMakePair( 2, 0));
    t_points.append(qMakePair( 2, 1));
    t_points.append(qMakePair( 2, 2));
    begin = 0;
    end = 5;
    qSort(t_points);
    setPoints(&t_points);
    potentialPoints.clear();
    newPoints.clear();

    findPotentialPoints();
    findNewPoints();
    qSort(newPoints);
    QCOMPARE(newPoints.size(), 5);
    QCOMPARE(newPoints[0],qMakePair( 1, 0));
    QCOMPARE(newPoints[1],qMakePair( 1, 2));
    QCOMPARE(newPoints[2],qMakePair( 2, 1));
    QCOMPARE(newPoints[3],qMakePair( 2, 2));
    QCOMPARE(newPoints[4],qMakePair( 3, 1));

    t_points.clear();
    t_points.append(newPoints);
    potentialPoints.clear();
    newPoints.clear();
    findPotentialPoints();
    findNewPoints();
    qSort(newPoints);
    QCOMPARE(newPoints.size(), 5);
    QCOMPARE(newPoints[0],qMakePair( 1, 2));
    QCOMPARE(newPoints[1],qMakePair( 2, 0));
    QCOMPARE(newPoints[2],qMakePair( 2, 2));
    QCOMPARE(newPoints[3],qMakePair( 3, 1));
    QCOMPARE(newPoints[4],qMakePair( 3, 2));

    t_points.clear();
    t_points.append(newPoints);
    potentialPoints.clear();
    newPoints.clear();
    findPotentialPoints();
    findNewPoints();
    qSort(newPoints);
    QCOMPARE(newPoints.size(), 5);
    QCOMPARE(newPoints[0],qMakePair( 1, 1));
    QCOMPARE(newPoints[1],qMakePair( 2, 2));
    QCOMPARE(newPoints[2],qMakePair( 2, 3));
    QCOMPARE(newPoints[3],qMakePair( 3, 1));
    QCOMPARE(newPoints[4],qMakePair( 3, 2));

    t_points.clear();
    t_points.append(newPoints);
    potentialPoints.clear();
    newPoints.clear();
    findPotentialPoints();
    findNewPoints();
    qSort(newPoints);
    QCOMPARE(newPoints.size(), 5);
    QCOMPARE(newPoints[0],qMakePair( 1, 2));
    QCOMPARE(newPoints[1],qMakePair( 2, 3));
    QCOMPARE(newPoints[2],qMakePair( 3, 1));
    QCOMPARE(newPoints[3],qMakePair( 3, 2));
    QCOMPARE(newPoints[4],qMakePair( 3, 3));

    potentialPoints.clear();
    newPoints.clear();
}

void Test_GOL_Points::test_findNeighbours()
{
    endlessField = false;
    numberOfCells = 10;
    QVector<QPair<int, int>> neighbours = findNeighbors(0,0);
    QCOMPARE(neighbours.size(), 8);
    QCOMPARE(neighbours[0],qMakePair(-1,-1));
    QCOMPARE(neighbours[1],qMakePair(-1, 0));
    QCOMPARE(neighbours[2],qMakePair(-1, 1));
    QCOMPARE(neighbours[3],qMakePair( 0,-1));
    QCOMPARE(neighbours[4],qMakePair( 0, 1));
    QCOMPARE(neighbours[5],qMakePair( 1,-1));
    QCOMPARE(neighbours[6],qMakePair( 1, 0));
    QCOMPARE(neighbours[7],qMakePair( 1, 1));

    neighbours.clear();
    neighbours = findNeighbors(10,10);
    QCOMPARE(neighbours.size(), 3);
    QCOMPARE(neighbours[0],qMakePair( 9, 9));
    QCOMPARE(neighbours[1],qMakePair( 9,10));
    QCOMPARE(neighbours[2],qMakePair(10, 9));

    neighbours.clear();
    endlessField = true;
    neighbours = findNeighbors(10,10);
    QCOMPARE(neighbours.size(), 8);
    QCOMPARE(neighbours[0],qMakePair(  9,  9));
    QCOMPARE(neighbours[1],qMakePair(  9, 10));
    QCOMPARE(neighbours[2],qMakePair(  9,-10));
    QCOMPARE(neighbours[3],qMakePair( 10,  9));
    QCOMPARE(neighbours[4],qMakePair( 10,-10));
    QCOMPARE(neighbours[5],qMakePair(-10,  9));
    QCOMPARE(neighbours[6],qMakePair(-10, 10));
    QCOMPARE(neighbours[7],qMakePair(-10,-10));
}

void Test_GOL_Points::test_countPointsAround()
{
    QVector<QPair<int,int>> t_points;
    numberOfCells = 10;
    t_points.clear();
    t_points.append(qMakePair(-2,-1));//     ****
    t_points.append(qMakePair(-2, 0));//  ****
    t_points.append(qMakePair(-2, 1));//  **0*
    t_points.append(qMakePair(-1,-1));//  ****
    t_points.append(qMakePair(-1, 0));//   *
    t_points.append(qMakePair(-1, 1));//
    t_points.append(qMakePair(-1, 2));//
    t_points.append(qMakePair( 0,-1));
    t_points.append(qMakePair( 0, 1));
    t_points.append(qMakePair( 1,-2));
    t_points.append(qMakePair( 1,-1));
    t_points.append(qMakePair( 1, 0));
    t_points.append(qMakePair( 1, 1));
    t_points.append(qMakePair( 2,-2));
    t_points.append(qMakePair( 3,-2));
    t_points.append(qMakePair( 4,-2));
    qSort(t_points);
    setPoints(&t_points);

    QVector<QPair<int, int> > neighbors;
    neighbors = findNeighbors( 0, 0);
    QCOMPARE( countPointsAround(neighbors), (unsigned short) 8 );
    neighbors.clear();
    neighbors = findNeighbors(-1, 0);
    QCOMPARE( countPointsAround(neighbors), (unsigned short) 7);
    neighbors.clear();
    neighbors = findNeighbors(-1, 1);
    QCOMPARE( countPointsAround(neighbors), (unsigned short) 5);
    neighbors.clear();
    neighbors = findNeighbors( 1, 0);
    QCOMPARE( countPointsAround(neighbors), (unsigned short) 4);
    neighbors.clear();
    neighbors = findNeighbors( 1,-2);
    QCOMPARE( countPointsAround(neighbors), (unsigned short) 3);
    neighbors.clear();
    neighbors = findNeighbors( 3,-2);
    QCOMPARE( countPointsAround(neighbors), (unsigned short) 2);
    neighbors.clear();
    neighbors = findNeighbors( 4,-2);
    QCOMPARE( countPointsAround(neighbors), (unsigned short) 1);

}

void Test_GOL_Points::test_countPointsAroundAndAddPotentialPoints()
{
    QVector<QPair<int,int>> t_points;
    numberOfCells = 10;
    t_points.clear();
    t_points.append(qMakePair(-2,-1));//     ****
    t_points.append(qMakePair(-2, 0));//  ****
    t_points.append(qMakePair(-2, 1));//  **0*
    t_points.append(qMakePair(-1,-1));//  ****
    t_points.append(qMakePair(-1, 0));//   *
    t_points.append(qMakePair(-1, 1));//
    t_points.append(qMakePair(-1, 2));//
    t_points.append(qMakePair( 0,-1));
    t_points.append(qMakePair( 0, 1));
    t_points.append(qMakePair( 1,-2));
    t_points.append(qMakePair( 1,-1));
    t_points.append(qMakePair( 1, 0));
    t_points.append(qMakePair( 1, 1));
    t_points.append(qMakePair( 2,-2));
    t_points.append(qMakePair( 3,-2));
    t_points.append(qMakePair( 4,-2));
    qSort(t_points);
    setPoints(&t_points);
    potentialPoints.clear();

    QVector<QPair<int, int> > neighbors;
    neighbors = findNeighbors( 0, 0);
    auto actual = countPointsAroundAndAddPotentialPoints(neighbors);
    QCOMPARE( actual, (unsigned short) 8 );
    QCOMPARE( potentialPoints.size(), 0);

    neighbors.clear();
    neighbors = findNeighbors( 1, 0);
    actual = countPointsAroundAndAddPotentialPoints(neighbors);
    QCOMPARE( actual, (unsigned short) 4 );
    QCOMPARE( potentialPoints.size(), 4);
    QCOMPARE( potentialPoints[0], qMakePair( 0, 0));
    QCOMPARE( potentialPoints[3], qMakePair( 2, 1));
    potentialPoints.clear();

    neighbors.clear();
    neighbors = findNeighbors( 2, 0);
    actual = countPointsAroundAndAddPotentialPoints(neighbors);
    QCOMPARE( actual, (unsigned short) 3 );
    QCOMPARE( potentialPoints.size(), 5);
    QCOMPARE( potentialPoints[0], qMakePair( 2,-1));
    QCOMPARE( potentialPoints[4], qMakePair( 3, 1));
    potentialPoints.clear();
}

void Test_GOL_Points::test_addToPotentialPoints()
{
    potentialPoints.clear();
    QCOMPARE( potentialPoints.size(), 0);
    addToPotentialPoints(qMakePair( 0, 0));
    QCOMPARE( potentialPoints.size(), 1);
    addToPotentialPoints(qMakePair( 0, 0));
    QCOMPARE( potentialPoints.size(), 1);
    addToPotentialPoints(qMakePair( 0,-1));
    QCOMPARE( potentialPoints.size(), 2);
    addToPotentialPoints(qMakePair( 0,-1));
    QCOMPARE( potentialPoints.size(), 2);
    addToPotentialPoints(qMakePair( 0, 0));
    QCOMPARE( potentialPoints.size(), 2);
    QCOMPARE( potentialPoints[0], qMakePair( 0,-1));
    QCOMPARE( potentialPoints[1], qMakePair( 0, 0));
    potentialPoints.clear();
}

void Test_GOL_Points::test_pointIsOutOfField()
{
    numberOfCells = 4;
    QVector<QPair<int,int>> t_points;
    t_points.append(qMakePair(-5, 0));
    t_points.append(qMakePair( 0, 5));
    t_points.append(qMakePair( 0, 0));
    t_points.append(qMakePair(-2,-2));
    t_points.append(qMakePair( 2, 2));
    t_points.append(qMakePair( 4, 4));
    t_points.append(qMakePair(-4,-4));
    setPoints(&t_points);

    auto itP = points->constBegin();
    for(int i=0; i<7; i++,itP++ ){
        if( i < 2 )
            QVERIFY(!pointOnField(itP));
        else{
            //QEXPECT_FAIL("", "OK_2 - designful error", Continue);
            QVERIFY(pointOnField(itP));
        }
    }
}

void Test_GOL_Points::test_pointsConsist()
{
    QVector<QPair<int,int>> t_points;
    numberOfCells = 10;

    for(int i=-2; i<5; i++)
        for(int j=-2; j<5; j++)
            t_points.append(qMakePair( i, j));

    qSort(t_points);
    setPoints(&t_points);

    for(int i=-2; i<5; i++)
        for(int j=-2; j<5; j++)
            QVERIFY(pointsConsist(qMakePair( i, j)));

    QVERIFY(!pointsConsist(qMakePair(-3, 0)));
    QVERIFY(!pointsConsist(qMakePair( 0, 6)));
    QVERIFY(!pointsConsist(qMakePair(-3,-3)));
    QVERIFY(!pointsConsist(qMakePair( 4, 6)));
    QVERIFY(!pointsConsist(qMakePair( 3,-3)));
}

QTEST_MAIN(Test_GOL_Points)

//#include "tst_gol.moc"
