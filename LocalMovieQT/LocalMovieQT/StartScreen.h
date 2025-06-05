#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class StartScreen : public QWidget {
	Q_OBJECT
public:
	StartScreen(QWidget* parent = nullptr);
signals:
	void adminModeSelected();
	void userModeSelected();
	void exitSelected();
};