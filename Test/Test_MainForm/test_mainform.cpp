#include <QString>
#include <QtTest>
#include "../../mainwindow.h"

class Test_GOL_MainForm : public QObject
{
    Q_OBJECT

public:
    Test_GOL_MainForm();

private Q_SLOTS:
    void testCase1_data();
    void testCase1();
    void test_recountCoordinates_data();
    void test_recountCoordinates();
};

Test_GOL_MainForm::Test_GOL_MainForm()
{
}

void Test_GOL_MainForm::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

void Test_GOL_MainForm::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

void Test_GOL_MainForm::test_recountCoordinates_data()
{
    QTest::addColumn<int>("actual");
    QTest::addColumn<int>("expected");

    MainWindow *mw = new MainWindow() ;
    int x;
    x = mw->recountCoordinates( 33, 'X');
        QTest::newRow("X=  33") << x << 32;
    x = mw->recountCoordinates(-32, 'X');
        QTest::newRow("X= -33") << x << -32;
    x = mw->recountCoordinates( 0, 'X');
        QTest::newRow("X=   0") << x << 0;
    x = mw->recountCoordinates( 1, 'X');
        QTest::newRow("X=   1") << x << 0;
    x = mw->recountCoordinates(-1, 'X');
        QTest::newRow("X=  -1") << x << 0;

    x = mw->recountCoordinates(-4, 'X');// X borders
        QTest::newRow("X=  -4") << x << -8;
    x = mw->recountCoordinates(-3, 'X');
        QTest::newRow("X=  -3") << x << 0;
    x = mw->recountCoordinates( 4, 'X');
        QTest::newRow("X=   4") << x <<  0;
    x = mw->recountCoordinates( 5, 'X');
        QTest::newRow("X=   5") << x << 8;

    x = mw->recountCoordinates( 33, 'Y');
        QTest::newRow("Y=  33") << x << 32;
    x = mw->recountCoordinates(-33, 'Y');
        QTest::newRow("Y= -33") << x << -32;
    x = mw->recountCoordinates( 0, 'Y');
        QTest::newRow("Y=   0") << x << 0;
    x = mw->recountCoordinates( 1, 'Y');
        QTest::newRow("Y=   1") << x << 0;
    x = mw->recountCoordinates(-1, 'Y');
        QTest::newRow("Y=  -1") << x << 0;

    x = mw->recountCoordinates(-5, 'Y');// Y borders
        QTest::newRow("Y=  -5") << x << -8;
    x = mw->recountCoordinates(-4, 'Y');
        QTest::newRow("Y=  -4") << x << 0;
    x = mw->recountCoordinates( 3, 'Y');
        QTest::newRow("Y=   3") << x <<  0;
    x = mw->recountCoordinates( 4, 'Y');
        QTest::newRow("Y=   4") << x << 8;
}

void Test_GOL_MainForm::test_recountCoordinates()
{
    QFETCH(int, actual);
    QFETCH(int, expected);
    QCOMPARE(actual, expected);
}

QTEST_MAIN(Test_GOL_MainForm)

#include "test_mainform.moc"
