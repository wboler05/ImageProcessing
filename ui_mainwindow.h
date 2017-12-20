/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "imagewidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionLoad;
    QAction *actionExit;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *swag_btn;
    QFrame *line;
    QLabel *label;
    QSpinBox *kernel_size_sb;
    QFrame *line_2;
    QLabel *label_2;
    QDoubleSpinBox *std_dev_x_dsb;
    QFrame *line_3;
    QLabel *label_3;
    QDoubleSpinBox *std_dev_y_dsb;
    QSplitter *splitter_3;
    QSplitter *splitter_2;
    QGroupBox *red_gb;
    QHBoxLayout *horizontalLayout;
    ImageWidget *red_ogl;
    QGroupBox *green_gb;
    QHBoxLayout *horizontalLayout_2;
    ImageWidget *green_ogl;
    QGroupBox *blue_gb;
    QHBoxLayout *horizontalLayout_3;
    ImageWidget *blue_ogl;
    QSplitter *splitter;
    QGroupBox *input_gb;
    QHBoxLayout *horizontalLayout_4;
    ImageWidget *input_ogl;
    QGroupBox *output_gb;
    QHBoxLayout *horizontalLayout_5;
    ImageWidget *output_ogl;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1030, 558);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_6 = new QHBoxLayout(groupBox);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        swag_btn = new QPushButton(groupBox);
        swag_btn->setObjectName(QStringLiteral("swag_btn"));
        QFont font;
        font.setFamily(QStringLiteral("MMCenturyOld"));
        swag_btn->setFont(font);

        horizontalLayout_6->addWidget(swag_btn);

        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(line);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_6->addWidget(label);

        kernel_size_sb = new QSpinBox(groupBox);
        kernel_size_sb->setObjectName(QStringLiteral("kernel_size_sb"));

        horizontalLayout_6->addWidget(kernel_size_sb);

        line_2 = new QFrame(groupBox);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(line_2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_6->addWidget(label_2);

        std_dev_x_dsb = new QDoubleSpinBox(groupBox);
        std_dev_x_dsb->setObjectName(QStringLiteral("std_dev_x_dsb"));
        std_dev_x_dsb->setMaximum(99999);

        horizontalLayout_6->addWidget(std_dev_x_dsb);

        line_3 = new QFrame(groupBox);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(line_3);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_6->addWidget(label_3);

        std_dev_y_dsb = new QDoubleSpinBox(groupBox);
        std_dev_y_dsb->setObjectName(QStringLiteral("std_dev_y_dsb"));
        std_dev_y_dsb->setMaximum(99999);

        horizontalLayout_6->addWidget(std_dev_y_dsb);


        verticalLayout->addWidget(groupBox);

        splitter_3 = new QSplitter(centralWidget);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Vertical);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        red_gb = new QGroupBox(splitter_2);
        red_gb->setObjectName(QStringLiteral("red_gb"));
        horizontalLayout = new QHBoxLayout(red_gb);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        red_ogl = new ImageWidget(red_gb);
        red_ogl->setObjectName(QStringLiteral("red_ogl"));

        horizontalLayout->addWidget(red_ogl);

        splitter_2->addWidget(red_gb);
        green_gb = new QGroupBox(splitter_2);
        green_gb->setObjectName(QStringLiteral("green_gb"));
        horizontalLayout_2 = new QHBoxLayout(green_gb);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        green_ogl = new ImageWidget(green_gb);
        green_ogl->setObjectName(QStringLiteral("green_ogl"));

        horizontalLayout_2->addWidget(green_ogl);

        splitter_2->addWidget(green_gb);
        blue_gb = new QGroupBox(splitter_2);
        blue_gb->setObjectName(QStringLiteral("blue_gb"));
        horizontalLayout_3 = new QHBoxLayout(blue_gb);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        blue_ogl = new ImageWidget(blue_gb);
        blue_ogl->setObjectName(QStringLiteral("blue_ogl"));

        horizontalLayout_3->addWidget(blue_ogl);

        splitter_2->addWidget(blue_gb);
        splitter_3->addWidget(splitter_2);
        splitter = new QSplitter(splitter_3);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        input_gb = new QGroupBox(splitter);
        input_gb->setObjectName(QStringLiteral("input_gb"));
        horizontalLayout_4 = new QHBoxLayout(input_gb);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        input_ogl = new ImageWidget(input_gb);
        input_ogl->setObjectName(QStringLiteral("input_ogl"));

        horizontalLayout_4->addWidget(input_ogl);

        splitter->addWidget(input_gb);
        output_gb = new QGroupBox(splitter);
        output_gb->setObjectName(QStringLiteral("output_gb"));
        horizontalLayout_5 = new QHBoxLayout(output_gb);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        output_ogl = new ImageWidget(output_gb);
        output_ogl->setObjectName(QStringLiteral("output_ogl"));

        horizontalLayout_5->addWidget(output_ogl);

        splitter->addWidget(output_gb);
        splitter_3->addWidget(splitter);

        verticalLayout->addWidget(splitter_3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1030, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionSave);
        menuFile->addAction(actionLoad);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "Save...", Q_NULLPTR));
        actionLoad->setText(QApplication::translate("MainWindow", "Load...", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Gaussian Box", Q_NULLPTR));
        swag_btn->setText(QApplication::translate("MainWindow", "Swag", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Kernel Size", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Std Dev X", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Std Dev Y", Q_NULLPTR));
        red_gb->setTitle(QApplication::translate("MainWindow", "Red", Q_NULLPTR));
        green_gb->setTitle(QApplication::translate("MainWindow", "Green", Q_NULLPTR));
        blue_gb->setTitle(QApplication::translate("MainWindow", "Blue", Q_NULLPTR));
        input_gb->setTitle(QApplication::translate("MainWindow", "Input", Q_NULLPTR));
        output_gb->setTitle(QApplication::translate("MainWindow", "Output", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
