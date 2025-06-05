#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LocalMovieQT.h"

class LocalMovieQT : public QMainWindow
{
    Q_OBJECT

public:
    LocalMovieQT(QWidget *parent = nullptr);
    ~LocalMovieQT();

private:
    Ui::LocalMovieQTClass ui;
};
