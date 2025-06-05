/********************************************************************************
** Form generated from reading UI file 'LocalMovieQT.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCALMOVIEQT_H
#define UI_LOCALMOVIEQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LocalMovieQTClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LocalMovieQTClass)
    {
        if (LocalMovieQTClass->objectName().isEmpty())
            LocalMovieQTClass->setObjectName("LocalMovieQTClass");
        LocalMovieQTClass->resize(600, 400);
        menuBar = new QMenuBar(LocalMovieQTClass);
        menuBar->setObjectName("menuBar");
        LocalMovieQTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LocalMovieQTClass);
        mainToolBar->setObjectName("mainToolBar");
        LocalMovieQTClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(LocalMovieQTClass);
        centralWidget->setObjectName("centralWidget");
        LocalMovieQTClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(LocalMovieQTClass);
        statusBar->setObjectName("statusBar");
        LocalMovieQTClass->setStatusBar(statusBar);

        retranslateUi(LocalMovieQTClass);

        QMetaObject::connectSlotsByName(LocalMovieQTClass);
    } // setupUi

    void retranslateUi(QMainWindow *LocalMovieQTClass)
    {
        LocalMovieQTClass->setWindowTitle(QCoreApplication::translate("LocalMovieQTClass", "LocalMovieQT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LocalMovieQTClass: public Ui_LocalMovieQTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCALMOVIEQT_H
