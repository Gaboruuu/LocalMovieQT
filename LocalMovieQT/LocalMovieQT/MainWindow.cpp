#include "MainWindow.h"

MainWindow::MainWindow(ServiceAdmin& admin, ServiceUser& user, QWidget* parent)
	: QMainWindow(parent) {

	setFixedSize(1000, 600);

	stack = new QStackedWidget(this);

	startScreen = new StartScreen(this);
	userScreen = new UserScreen(user, this);
	adminScreen = new AdminScreen(admin, this);
	
	stack->addWidget(startScreen);
	stack->addWidget(userScreen);
	stack->addWidget(adminScreen);
	
	setCentralWidget(stack);
	connect(startScreen, &StartScreen::adminModeSelected, [this]() { stack->setCurrentIndex(2); });
	connect(startScreen, &StartScreen::userModeSelected, [this]() { stack->setCurrentIndex(1);});
	connect(startScreen, &StartScreen::exitSelected, this, &QMainWindow::close);

	connect(adminScreen, &AdminScreen::backSelected, [this]() { stack->setCurrentIndex(0); });
	connect(userScreen, &UserScreen::backSelected, [this]() { stack->setCurrentIndex(0); });

}