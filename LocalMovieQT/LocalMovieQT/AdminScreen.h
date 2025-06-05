#pragma once
#include <QWidget>
#include "ServiceAdmin.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QMessageBox>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFormLayout>
#include <QComboBox>
#include "RepoException.h"
#include "MovieValidater.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QShortcut>
#include "UndoRedo.h"

class AdminScreen : public QWidget {
    Q_OBJECT
public:
	AdminScreen(ServiceAdmin& admin, QWidget* parent = nullptr);
	~AdminScreen() {
		for (auto cmd : undoStack) {
			delete cmd;
		}
		for (auto cmd : redoStack) {
			delete cmd;
		}
	}

private:
	ServiceAdmin& adminService;
    QVBoxLayout* layout;
    QLabel* titleLabel;
    QPushButton* addMovieButton;
    QPushButton* removeMovieButton;
    QPushButton* updateMovieButton;
    QPushButton* viewMoviesButton;
    QPushButton* backButton;

    QWidget* addMovieWidget = nullptr;
    QPushButton* addMovieConfirmButton = nullptr;
    QPushButton* addBackButton = nullptr;
	
    QWidget* removeMovieWidget = nullptr;
	QPushButton* removeMovieConfirmButton = nullptr;
    QPushButton* removeBackButton = nullptr;

	QComboBox* titleComboBox = nullptr;
	QWidget* updateMovieWidget = nullptr;
	QPushButton* updateMovieConfirmButton = nullptr;
	QPushButton* updateBackButton = nullptr;

	QWidget* viewMoviesWidget = nullptr;
	QPushButton* viewMoviesBackButton = nullptr;
	QTableWidget* moviesTableWidget = nullptr;

	QListWidget* movieList = nullptr;

    void hideAdminWidgets();
	void showAdminWidgets();

	void createAddMovieWidget();
	void createRemoveMovieWidget();
	void createUpdateMovieWidget();
	void createViewMoviesWidget();

	void populateMoviesTable();
	void populateRemoveMovieList(QListWidget* movieList);
	void populateUpdateMovieList(QComboBox* titleComboBox);

	void refreshMovies();

	QPushButton* undoButton = nullptr;
	QPushButton* redoButton = nullptr;
	std::vector<Command*> undoStack;
	std::vector<Command*> redoStack;
	void undo();
	void redo();
	void clearRedoStack();

signals:
	void backSelected();
};