#pragma once
#include <QWidget>
#include "ServiceUser.h"
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
#include "WatchlistTableModel.h"

class UserScreen : public QWidget {
	Q_OBJECT
public:
	UserScreen(ServiceUser& user, QWidget* parent = nullptr);

private:
	ServiceUser& userService;
	QVBoxLayout* layout;
	QLabel* titleLabel;
	QPushButton* listMoviesButton;
	QPushButton* removeWathchlistButton;
	QPushButton* showWatchlistButton;
	QPushButton* displayFormatButton;
	QPushButton* backButton;
	
	void createListMoviesWidget();
	QWidget* listMoviesWidget = nullptr;
	QLabel* titleLabelMovie = nullptr;
	QLabel* genreLabel = nullptr;
	QLabel* yearLabel = nullptr;
	QLabel* likesLabel = nullptr;
	QLabel* addToWatchlistLabel = nullptr;
	QPushButton* addToWatchlistButton = nullptr;
	QPushButton* notAddToWatchlistButton = nullptr;
	QLabel* likedMoviesLabel = nullptr;
	QPushButton* likeButton = nullptr;
	QPushButton* notLikeButton = nullptr;

	void createRemoveWatchlistWidget();
	QWidget* removeWatchlistWidget = nullptr;
	QPushButton* removeMovieConfirmButton = nullptr;
	QPushButton* removeMovieBackButton = nullptr;
	QPushButton* removeBackButton = nullptr;
	QListWidget* movieList = nullptr;

	void createShowWatchlistWidget();
	QWidget* showWatchlistWidget = nullptr;
	QPushButton* showWatchlistBackButton = nullptr;
	WatchlistTableModel* watchlistModel = nullptr;
	QTableView* watchlistTableView = nullptr;

	void populateWatchlistTable();

	void createDisplayFormatWidget();
	QWidget* displayFormatWidget = nullptr;

	std::vector<Movie> movies;
	std::vector<Movie> watchlistMovies;
	void loadMovies(std::string genra);
	void nextMovie();
	void loadRemoveWatchlistMovies();
	int currentMovieIndex = 0;
	std::string currentGenre = "";


	void hideUserWidgets();
	void showUserWidgets();

signals:
	void backSelected();
};