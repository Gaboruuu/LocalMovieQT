#include "StartScreen.h"

StartScreen::StartScreen(QWidget* parent)
	: QWidget(parent) {
	QVBoxLayout* layout = new QVBoxLayout(this);
	QLabel* titleLabel = new QLabel("Welcome to Local Movie QT", this);
	QPushButton* adminButton = new QPushButton("Admin Mode", this);
	QPushButton* userButton = new QPushButton("User Mode", this);
	QPushButton* exitButton = new QPushButton("Exit", this);

	layout->addWidget(titleLabel);
	layout->addWidget(adminButton);
	layout->addWidget(userButton);
	layout->addWidget(exitButton);

	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

	adminButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 18px;");
	userButton->setStyleSheet("background-color: #008CBA; color: white; font-size: 18px;");
	exitButton->setStyleSheet("background-color: #f44336; color: white; font-size: 18px;");

	adminButton->setFixedHeight(50);
	userButton->setFixedHeight(50);
	exitButton->setFixedHeight(50);

	layout->setAlignment(Qt::AlignCenter);
	layout->setSpacing(20);
	layout->setContentsMargins(50, 50, 50, 50);
	setLayout(layout);
	setWindowTitle("Local Movie Manager");

	connect(adminButton, &QPushButton::clicked, this, &StartScreen::adminModeSelected);
	connect(userButton, &QPushButton::clicked, this, &StartScreen::userModeSelected);
	connect(exitButton, &QPushButton::clicked, this, &StartScreen::exitSelected);
}