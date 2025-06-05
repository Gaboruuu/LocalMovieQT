#pragma once
#include <QMainWIndow>
#include <QWidget>
#include <QStackedWidget>
#include "StartScreen.h"
#include "UserScreen.h"
#include "AdminScreen.h"
#include "ServiceAdmin.h"
#include "ServiceUser.h"


class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(ServiceAdmin& admin, ServiceUser& user, QWidget* parent = nullptr);

private:
	QStackedWidget* stack;
	StartScreen* startScreen;
	UserScreen* userScreen;
	AdminScreen* adminScreen;
};