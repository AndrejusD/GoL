/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButtonResetCounter;
    QLabel *label_3;
    QCheckBox *checkBox;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QFrame *line_2;
    QPushButton *pushButtonClearField;
    QPushButton *pushButtonStart;
    QCheckBox *checkBoxThreads;
    QLabel *label;
    QSlider *horizontalSlider;
    QGraphicsView *graphicsView;
    QFrame *line;
    QPushButton *pushButtonAddCells;
    QPushButton *pushButtonStop;
    QLCDNumber *lcdNumber;
    QLabel *label_4;
    QFrame *line_3;
    QLabel *label_numberOfPoints;
    QDial *dial;
    QLineEdit *lineEdit;
    QPushButton *pushButtonStep;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(943, 725);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMouseTracking(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButtonResetCounter = new QPushButton(centralWidget);
        pushButtonResetCounter->setObjectName(QStringLiteral("pushButtonResetCounter"));

        gridLayout->addWidget(pushButtonResetCounter, 17, 0, 1, 2);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 8, 0, 1, 1);

        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setChecked(true);

        gridLayout->addWidget(checkBox, 2, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 15, 0, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 5, 0, 1, 1);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 20, 0, 1, 2);

        pushButtonClearField = new QPushButton(centralWidget);
        pushButtonClearField->setObjectName(QStringLiteral("pushButtonClearField"));

        gridLayout->addWidget(pushButtonClearField, 16, 0, 1, 2);

        pushButtonStart = new QPushButton(centralWidget);
        pushButtonStart->setObjectName(QStringLiteral("pushButtonStart"));

        gridLayout->addWidget(pushButtonStart, 22, 0, 1, 2);

        checkBoxThreads = new QCheckBox(centralWidget);
        checkBoxThreads->setObjectName(QStringLiteral("checkBoxThreads"));
        checkBoxThreads->setChecked(true);

        gridLayout->addWidget(checkBoxThreads, 4, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(9);
        horizontalSlider->setPageStep(1);
        horizontalSlider->setValue(3);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 6, 0, 1, 2);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setSizeIncrement(QSize(0, 0));
        graphicsView->setMouseTracking(true);
        graphicsView->setAutoFillBackground(false);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        graphicsView->setBackgroundBrush(brush);
        QBrush brush1(QColor(36, 36, 36, 255));
        brush1.setStyle(Qt::CrossPattern);
        graphicsView->setForegroundBrush(brush1);
        graphicsView->setInteractive(true);
        graphicsView->setSceneRect(QRectF(0, 0, 0, 0));
        graphicsView->setDragMode(QGraphicsView::NoDrag);
        graphicsView->setCacheMode(QGraphicsView::CacheBackground);
        graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
        graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

        gridLayout->addWidget(graphicsView, 0, 2, 24, 1);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 7, 0, 1, 2);

        pushButtonAddCells = new QPushButton(centralWidget);
        pushButtonAddCells->setObjectName(QStringLiteral("pushButtonAddCells"));

        gridLayout->addWidget(pushButtonAddCells, 18, 0, 1, 2);

        pushButtonStop = new QPushButton(centralWidget);
        pushButtonStop->setObjectName(QStringLiteral("pushButtonStop"));
        pushButtonStop->setEnabled(false);

        gridLayout->addWidget(pushButtonStop, 23, 0, 1, 2);

        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(lcdNumber, 9, 0, 1, 2);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 13, 0, 1, 1);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 12, 0, 1, 2);

        label_numberOfPoints = new QLabel(centralWidget);
        label_numberOfPoints->setObjectName(QStringLiteral("label_numberOfPoints"));

        gridLayout->addWidget(label_numberOfPoints, 14, 0, 1, 1);

        dial = new QDial(centralWidget);
        dial->setObjectName(QStringLiteral("dial"));
        dial->setEnabled(false);
        dial->setMouseTracking(false);
        dial->setFocusPolicy(Qt::WheelFocus);
        dial->setMaximum(200);
        dial->setTracking(true);
        dial->setWrapping(false);

        gridLayout->addWidget(dial, 11, 0, 1, 1);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setLayoutDirection(Qt::LeftToRight);
        lineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lineEdit, 1, 0, 1, 2);

        pushButtonStep = new QPushButton(centralWidget);
        pushButtonStep->setObjectName(QStringLiteral("pushButtonStep"));

        gridLayout->addWidget(pushButtonStep, 21, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Game Of Life", 0));
        pushButtonResetCounter->setText(QApplication::translate("MainWindow", "Reset counter", 0));
        label_3->setText(QApplication::translate("MainWindow", "Step calc. time (ms):", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Endless field", 0));
        label_2->setText(QApplication::translate("MainWindow", "Speed:", 0));
        pushButtonClearField->setText(QApplication::translate("MainWindow", "Clear field", 0));
        pushButtonStart->setText(QApplication::translate("MainWindow", "Start", 0));
        checkBoxThreads->setText(QApplication::translate("MainWindow", "Use threads", 0));
        label->setText(QApplication::translate("MainWindow", "Field Size:", 0));
        pushButtonAddCells->setText(QApplication::translate("MainWindow", "Add points", 0));
        pushButtonStop->setText(QApplication::translate("MainWindow", "Stop", 0));
        label_4->setText(QApplication::translate("MainWindow", "Number of points:", 0));
        label_numberOfPoints->setText(QApplication::translate("MainWindow", "ABC", 0));
        lineEdit->setText(QApplication::translate("MainWindow", "80", 0));
        pushButtonStep->setText(QApplication::translate("MainWindow", "Step", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
