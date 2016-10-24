#include <QString>
#include <QtTest>
//#include <QtGui>
//#include <QMainWindow>
#include "../../mainwindow.h"
//#include "../../../build-GameOfLife-Desktop_Qt_5_6_1_MinGW_32bit-Debug/ui_mainwindow.h"


class Test_GOL_MainForm : public QObject
{
    Q_OBJECT

public:
    Test_GOL_MainForm();

private Q_SLOTS:
    void testCase1_data();
    void testCase1();
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

void Test_GOL_MainForm::test_recountCoordinates()
{
    //MainWindow *mw = new MainWindow() ;
    //int X = mw->recountCoordinates(33, 'X');
    //QCOMPARE( X , 24);
}

QTEST_MAIN(Test_GOL_MainForm)

#include "test_mainform.moc"
