#include "UserScreen.h"

UserScreen::UserScreen(ServiceUser& user, QWidget* parent) : QWidget(parent), userService(user) {
	layout  = new QVBoxLayout(this);
	titleLabel = new QLabel("User Screen", this);
	listMoviesButton = new QPushButton("List Movies", this);
	removeWathchlistButton = new QPushButton("Remove from Watchlist", this);
	showWatchlistButton = new QPushButton("Show Watchlist", this);
	displayFormatButton = new QPushButton("Display Format", this);
	backButton = new QPushButton("Back", this);
	layout->addWidget(titleLabel);
	layout->addWidget(listMoviesButton);
	layout->addWidget(removeWathchlistButton);
	layout->addWidget(showWatchlistButton);
	layout->addWidget(displayFormatButton);
	layout->addWidget(backButton);

	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
	listMoviesButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 18px;");
	removeWathchlistButton->setStyleSheet("background-color: #f44336; color: white; font-size: 18px;");
	showWatchlistButton->setStyleSheet("background-color: #008CBA; color: white; font-size: 18px;");
	displayFormatButton->setStyleSheet("background-color: #FF9800; color: white; font-size: 18px;");
	backButton->setStyleSheet("background-color: #9E9E9E; color: white; font-size: 18px;");
	listMoviesButton->setFixedHeight(50);
	removeWathchlistButton->setFixedHeight(50);
	showWatchlistButton->setFixedHeight(50);
	displayFormatButton->setFixedHeight(50);
	backButton->setFixedHeight(50);
	listMoviesButton->setFixedWidth(250);
	layout->setAlignment(Qt::AlignCenter);
	layout->setSpacing(20);
	layout->setContentsMargins(50, 50, 50, 50);
	setLayout(layout);

	createListMoviesWidget();
	connect(listMoviesButton, &QPushButton::clicked, this, [this]() {
		hideUserWidgets();
		loadMovies("");
		listMoviesWidget->show();
	});

	createRemoveWatchlistWidget();
	connect(removeWathchlistButton, &QPushButton::clicked, this, [this]() {
		hideUserWidgets();
		removeWatchlistWidget->show();
		loadMovies("");
	});

	createShowWatchlistWidget();
	connect(showWatchlistButton, &QPushButton::clicked, this, [this]() {
		hideUserWidgets();
		showWatchlistWidget->show();
		watchlistMovies = userService.get_watchlist();
		populateWatchlistTable();
	});

	createDisplayFormatWidget();
	connect(displayFormatButton, &QPushButton::clicked, this, [this]() {
		hideUserWidgets();
		watchlistMovies = userService.get_watchlist();
		displayFormatWidget->show();
	});

	connect(backButton, &QPushButton::clicked, this, &UserScreen::backSelected);
}

void UserScreen::hideUserWidgets() {
	titleLabel->hide();
	listMoviesButton->hide();
	removeWathchlistButton->hide();
	showWatchlistButton->hide();
	displayFormatButton->hide();
	backButton->hide();
}

void UserScreen::showUserWidgets() {
	titleLabel->show();
	listMoviesButton->show();
	removeWathchlistButton->show();
	showWatchlistButton->show();
	displayFormatButton->show();
	backButton->show();
}


void UserScreen::createListMoviesWidget() {
	listMoviesWidget = new QWidget(this);
	
	QHBoxLayout* listMainLayot = new QHBoxLayout(listMoviesWidget);
	QFormLayout* leftLayout = new QFormLayout(listMoviesWidget);
	QVBoxLayout* rightLayout = new QVBoxLayout(listMoviesWidget);

	titleLabelMovie = new QLabel("placeholder", listMoviesWidget);
	genreLabel = new QLabel("placeholder", listMoviesWidget);
	yearLabel = new QLabel("placeholder", listMoviesWidget);
	likesLabel = new QLabel("placeholder", listMoviesWidget);

	titleLabelMovie->setMinimumWidth(500);

	leftLayout->addRow(new QLabel("<span style='font-size:20px; color:#1976D2; font-weight:bold;'>Title: </span>"), titleLabelMovie);
	leftLayout->addRow(new QLabel("<span style='font-size:20px; color:#1976D2; font-weight:bold;'>Genre: </span>"), genreLabel);
	leftLayout->addRow(new QLabel("<span style='font-size:20px; color:#1976D2; font-weight:bold;'>Year:  </span>"), yearLabel);
	leftLayout->addRow(new QLabel("<span style='font-size:20px; color:#1976D2; font-weight:bold;'>Likes: </span>"), likesLabel);

	listMainLayot->addLayout(leftLayout);

	//design
	leftLayout->setAlignment(Qt::AlignLeft);
	titleLabelMovie->setStyleSheet("font-size: 18px; font-weight: bold;");
	genreLabel->setStyleSheet("font-size: 16px;");
	yearLabel->setStyleSheet("font-size: 16px;");
	likesLabel->setStyleSheet("font-size: 16px;");
	leftLayout->setContentsMargins(20, 20, 20, 20);


	QVBoxLayout* likedMoviesLayout = new QVBoxLayout(listMoviesWidget);
	likedMoviesLabel = new QLabel("Did you like the Trailer?", listMoviesWidget);
	QHBoxLayout* likedMoviesButtonsLayout = new QHBoxLayout(listMoviesWidget);
	likeButton = new QPushButton("Like", listMoviesWidget);
	notLikeButton = new QPushButton("No", listMoviesWidget);
	likedMoviesButtonsLayout->addWidget(likeButton);
	likedMoviesButtonsLayout->addWidget(notLikeButton);
	
	likedMoviesLayout->addWidget(likedMoviesLabel);
	likedMoviesLayout->addLayout(likedMoviesButtonsLayout);

	rightLayout->addLayout(likedMoviesLayout);

	//design
	likedMoviesLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
	likedMoviesLayout->setContentsMargins(20, 20, 20, 20);
	likeButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 18px;");
	notLikeButton->setStyleSheet("background-color: #f44336; color: white; font-size: 18px;");
	likedMoviesLabel->setMidLineWidth(300);


	QVBoxLayout* addToWatchlistLayout = new QVBoxLayout(listMoviesWidget);
	addToWatchlistLabel = new QLabel("", listMoviesWidget);
	addToWatchlistButton = new QPushButton("Add", listMoviesWidget);
	notAddToWatchlistButton = new QPushButton("No", listMoviesWidget);
	QHBoxLayout* addToWatchlistButtonsLayout = new QHBoxLayout(listMoviesWidget);

	addToWatchlistButton->hide();
	notAddToWatchlistButton->hide();

	//design
	addToWatchlistLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
	addToWatchlistLayout->setContentsMargins(20, 20, 20, 20);
	addToWatchlistButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 18px;");
	notAddToWatchlistButton->setStyleSheet("background-color: #f44336; color: white; font-size: 18px;");

	addToWatchlistButtonsLayout->addWidget(addToWatchlistButton);
	addToWatchlistButtonsLayout->addWidget(notAddToWatchlistButton);

	addToWatchlistLayout->addWidget(addToWatchlistLabel);
	addToWatchlistLayout->addLayout(addToWatchlistButtonsLayout);

	rightLayout->addLayout(addToWatchlistLayout);

	QPushButton* continueButton = new QPushButton("Continue", listMoviesWidget);
	QPushButton* backButtonList = new QPushButton("Back", listMoviesWidget);
	rightLayout->addWidget(continueButton);
	rightLayout->addWidget(backButtonList);

	listMainLayot->addLayout(rightLayout);

	//design
	continueButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 18px;");
	backButtonList->setStyleSheet("background-color: #f44336; color: white; font-size: 18px;");

	listMoviesWidget->setLayout(listMainLayot);
	listMoviesWidget->hide();
	layout->addWidget(listMoviesWidget);

	QLineEdit* genraInput = new QLineEdit(listMoviesWidget);
	genraInput->setPlaceholderText("Enter genre to filter (optional)");
	leftLayout->addRow(new QLabel("<span style='font-size:20px; color:#1976D2; font-weight:bold;'>Filter by Genre: </span>"), genraInput);

	loadMovies("");
	connect(genraInput, &QLineEdit::returnPressed, this, [this, genraInput]() {
		std::string genre = genraInput->text().toStdString();
		loadMovies(genre);
		if (movies.empty()) {
			QMessageBox::information(this, "No Movies", "No movies available for the selected genre.");
			return;
		}
		currentMovieIndex = 0;
		nextMovie();
		});

	// Connect signals and slots
	connect(backButtonList, &QPushButton::clicked, this, [this]() {
		listMoviesWidget->hide();
		showUserWidgets();
	});

	connect(continueButton, &QPushButton::clicked, this, [this]() {	
		nextMovie();
	});

	connect(likeButton, &QPushButton::clicked, this, [this]() {
		userService.like_movie(movies[currentMovieIndex - 1].get_title());
		QMessageBox::information(this, "Like", "You liked the movie!");
		currentMovieIndex--;
		nextMovie();

		std::vector<Movie> watchlist = userService.get_watchlist();
		bool found = false;
		for (const auto& movie : watchlist) {
			if (movie.get_title() == movies[currentMovieIndex - 1].get_title()) {
				found = true;
				break;
			}
		}
		if (!found) {
			addToWatchlistLabel->setText("Do you want to add it to your watchlist?");
			addToWatchlistButton->show();
			notAddToWatchlistButton->show();
		}
		else {
			addToWatchlistLabel->setText("Movie already in watchlist.");
			addToWatchlistButton->hide();
			notAddToWatchlistButton->hide();
		}

		likeButton->hide();
		notLikeButton->hide();
		likedMoviesLabel->setText("You liked the movie!");

	});

	connect(notLikeButton, &QPushButton::clicked, this, [this]() {
		nextMovie();
	});

	connect(addToWatchlistButton, &QPushButton::clicked, this, [this]() {
		userService.add_movie_to_watchlist(movies[currentMovieIndex - 1].get_title());
		QMessageBox::information(this, "Add to Watchlist", "Movie added to watchlist!");
		addToWatchlistLabel->setText("Movie added to watchlist.");
		addToWatchlistButton->hide();
		notAddToWatchlistButton->hide();
		loadRemoveWatchlistMovies();
	});

	connect(notAddToWatchlistButton, &QPushButton::clicked, this, [this]() {
		addToWatchlistLabel->setText("Movie not added to watchlist.");
		addToWatchlistButton->hide();
		notAddToWatchlistButton->hide();
	});



	nextMovie();
}

void UserScreen::nextMovie() {
	loadMovies(currentGenre);
	if (currentMovieIndex >= movies.size()) {
		currentMovieIndex = 0;
	}
	titleLabelMovie->setText(QString::fromStdString(movies[currentMovieIndex].get_title()));
	genreLabel->setText(QString::fromStdString(movies[currentMovieIndex].get_genre()));
	yearLabel->setText(QString::number(movies[currentMovieIndex].get_year()));
	likesLabel->setText(QString::number(movies[currentMovieIndex].get_likes()));
	currentMovieIndex++;

	addToWatchlistLabel->setText("");
	addToWatchlistButton->hide();
	notAddToWatchlistButton->hide();
	likedMoviesLabel->setText("Did you like the Trailer?");
	likeButton->show();
	notLikeButton->show();
}

void UserScreen::loadMovies(std::string genra) {
	if (genra.empty()) {
		movies = userService.get_movies();
		currentGenre = "";
	}
	else {
		try {
			movies = userService.get_movies_by_genre(genra);
			currentGenre = genra;
		}
		catch (const RepositoryException& e) {
			QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
			movies.clear();
			return;
		}
	}
	if (movies.empty()) {
		QMessageBox::information(this, "No Movies", "No movies available.");
		return;
	}

}

void UserScreen::createRemoveWatchlistWidget() {
	removeWatchlistWidget = new QWidget(this);
	QVBoxLayout* removeMovieLayout = new QVBoxLayout(removeWatchlistWidget);
	QLabel* removeMovieLabel = new QLabel("Select a movie to remove from watch list:", removeWatchlistWidget);
	movieList = new QListWidget(removeWatchlistWidget);
	removeMovieConfirmButton = new QPushButton("Remove Movie", removeWatchlistWidget);
	removeMovieLayout->addWidget(removeMovieLabel);
	removeMovieLayout->addWidget(movieList);
	removeMovieLayout->addWidget(removeMovieConfirmButton);
	removeBackButton = new QPushButton("Back", removeWatchlistWidget);
	removeMovieLayout->addWidget(removeBackButton);
	removeWatchlistWidget->setLayout(removeMovieLayout);
	removeWatchlistWidget->hide();
	layout->addWidget(removeWatchlistWidget);
	loadRemoveWatchlistMovies();

	connect(removeBackButton, &QPushButton::clicked, this, [this]() {
		removeWatchlistWidget->hide();
		showUserWidgets();
		});

	connect(removeMovieConfirmButton, &QPushButton::clicked, this, [this]() {
		QListWidget* movieList = removeWatchlistWidget->findChild<QListWidget*>();
		if (movieList) {
			QListWidgetItem* selectedItem = movieList->currentItem();
			if (selectedItem) {
				QString selectedMovieTitle = selectedItem->text();
				userService.remove_movie_from_watchlist(selectedMovieTitle.toStdString());
				QMessageBox::information(this, "Remove Movie", "Movie removed from watchlist!");
				movieList->takeItem(movieList->row(selectedItem));
			}
			else {
				QMessageBox::warning(this, "No Selection", "Please select a movie to remove.");
			}
		}
		});
}

void UserScreen::loadRemoveWatchlistMovies() {
	watchlistMovies = userService.get_watchlist();
	movieList->clear();
	for (const auto& movie : watchlistMovies) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(movie.get_title()));
		movieList->addItem(item);
	}
}

void UserScreen::createShowWatchlistWidget() {
	showWatchlistWidget = new QWidget(this);
	QVBoxLayout* showWatchlistLayout = new QVBoxLayout(showWatchlistWidget);
	QLabel* showWatchlistLabel = new QLabel("Your Watchlist:", showWatchlistWidget);
	
	watchlistModel = new WatchlistTableModel(this);
	watchlistTableView = new QTableView(showWatchlistWidget);
	watchlistTableView->setModel(watchlistModel);
	watchlistTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	watchlistTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	watchlistTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	showWatchlistBackButton = new QPushButton("Back", showWatchlistWidget);

	showWatchlistLayout->addWidget(showWatchlistLabel);
	showWatchlistLayout->addWidget(watchlistTableView);
	showWatchlistLayout->addWidget(showWatchlistBackButton);

	showWatchlistWidget->setLayout(showWatchlistLayout);
	showWatchlistWidget->hide();
	layout->addWidget(showWatchlistWidget);

	connect(showWatchlistBackButton, &QPushButton::clicked, this, [this]() {
		showWatchlistWidget->hide();
		showUserWidgets();
		});
}

void UserScreen::populateWatchlistTable() {
	watchlistModel->setMovies(watchlistMovies);
}

void UserScreen::createDisplayFormatWidget() {
	displayFormatWidget = new QWidget(this);
	QVBoxLayout* mainLayout = new QVBoxLayout(displayFormatWidget);
	QHBoxLayout* displayFormatLayout = new QHBoxLayout(displayFormatWidget);
	QLabel* displayFormatLabel = new QLabel("Select Display Format", displayFormatWidget);
	QPushButton* csvButton = new QPushButton("CSV", displayFormatWidget);
	QPushButton* htmlButton = new QPushButton("HTML", displayFormatWidget);
	QPushButton* backButtonDisplay = new QPushButton("Back", displayFormatWidget);

	csvButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 18px;");
	htmlButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 18px;");
	displayFormatLayout->addWidget(csvButton);
	displayFormatLayout->addWidget(htmlButton);
	displayFormatLayout->setAlignment(Qt::AlignCenter);
	
	backButtonDisplay->setStyleSheet("background-color: #f44336; color: white; font-size: 18px;");

	mainLayout->addWidget(displayFormatLabel);
	mainLayout->addLayout(displayFormatLayout);
	mainLayout->addWidget(backButtonDisplay);
	displayFormatLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
	displayFormatLabel->setAlignment(Qt::AlignCenter);
	displayFormatWidget->setLayout(mainLayout);
	displayFormatWidget->hide();
	layout->addWidget(displayFormatWidget);

	connect(csvButton, &QPushButton::clicked, this, [this]() {
		userService.display_watchlist("csv");
		QMessageBox::information(this, "Export to CSV", "Watchlist exported to CSV file.");
	});

	connect(htmlButton, &QPushButton::clicked, this, [this]() {
		userService.display_watchlist("html");
		QMessageBox::information(this, "Export to HTML", "Watchlist exported to HTML file.");
	});

	connect(backButtonDisplay, &QPushButton::clicked, this, [this]() {
		displayFormatWidget->hide();
		showUserWidgets();
		});
}