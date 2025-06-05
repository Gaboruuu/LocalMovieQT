#pragma once
#include "AdminScreen.h"

AdminScreen::AdminScreen(ServiceAdmin& admin, QWidget* parent)
	: QWidget(parent), adminService(admin) {
	layout = new QVBoxLayout(this);
	titleLabel = new QLabel("Admin Mode", this);
	addMovieButton = new QPushButton("Add Movie", this);
	removeMovieButton = new QPushButton("Remove Movie", this);
	updateMovieButton = new QPushButton("Update Movie", this);
	viewMoviesButton = new QPushButton("View Movies", this);
	backButton = new QPushButton("Back to Start Screen", this);
	undoButton = new QPushButton("Undo", this);
	redoButton = new QPushButton("Redo", this);
	layout->addWidget(titleLabel);
	layout->addWidget(addMovieButton);
	layout->addWidget(removeMovieButton);
	layout->addWidget(updateMovieButton);
	layout->addWidget(viewMoviesButton);
	layout->addWidget(backButton);
	layout->addWidget(undoButton);
	layout->addWidget(redoButton);
	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
	addMovieButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 18px;");
	removeMovieButton->setStyleSheet("background-color: #f44336; color: white; font-size: 18px;");
	updateMovieButton->setStyleSheet("background-color: #008CBA; color: white; font-size: 18px;");
	viewMoviesButton->setStyleSheet("background-color: #FF9800; color: white; font-size: 18px;");
	backButton->setStyleSheet("background-color: #9E9E9E; color: white; font-size: 18px;");
	undoButton->setStyleSheet("background-color: Purple; color: white; font-size: 18px;");
	redoButton->setStyleSheet("background-color: Blue; color: white; font-size: 18px;");
	addMovieButton->setFixedHeight(50);
	removeMovieButton->setFixedHeight(50);
	updateMovieButton->setFixedHeight(50);
	viewMoviesButton->setFixedHeight(50);
	backButton->setFixedHeight(50);
	layout->setAlignment(Qt::AlignCenter);
	layout->setSpacing(20);
	layout->setContentsMargins(50, 50, 50, 50);
	setLayout(layout);		

	createAddMovieWidget();
	connect(addMovieButton, &QPushButton::clicked, this, [this]() {
		hideAdminWidgets();
		refreshMovies();
		addMovieWidget->show();
	});

	createRemoveMovieWidget();
	connect(removeMovieButton, &QPushButton::clicked, this, [this]() {
		removeMovieWidget->show();
		refreshMovies();
		hideAdminWidgets();
	});

	createUpdateMovieWidget();
	connect(updateMovieButton, &QPushButton::clicked, this, [this]() {
		hideAdminWidgets();
		refreshMovies();
		updateMovieWidget->show();
		});
	createViewMoviesWidget();
	connect(viewMoviesButton, &QPushButton::clicked, this, [this]() {
		hideAdminWidgets();
		refreshMovies();
		viewMoviesWidget->show();
		});

	connect(backButton, &QPushButton::clicked, this, &AdminScreen::backSelected);
	connect(undoButton, &QPushButton::clicked, this, &AdminScreen::undo);
	connect(redoButton, &QPushButton::clicked, this, &AdminScreen::redo);

	QShortcut* undoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this);
	undoShortcut->setContext(Qt::WidgetWithChildrenShortcut);
	connect(undoShortcut, &QShortcut::activated, this, &AdminScreen::undo);

	QShortcut* redoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this);
	redoShortcut->setContext(Qt::WidgetWithChildrenShortcut);
	connect(redoShortcut, &QShortcut::activated, this, &AdminScreen::redo);
}

void AdminScreen::hideAdminWidgets() {
	addMovieButton->hide();
	removeMovieButton->hide();
	updateMovieButton->hide();
	viewMoviesButton->hide();
	backButton->hide();
	undoButton->hide();
	redoButton->hide();
}

void AdminScreen::showAdminWidgets() {
	addMovieButton->show();
	removeMovieButton->show();
	updateMovieButton->show();
	viewMoviesButton->show();
	backButton->show();
	undoButton->show();
	redoButton->show();
}

void AdminScreen::createAddMovieWidget() {
	addMovieWidget = new QWidget(this);
	QFormLayout* addMovieLayout = new QFormLayout(addMovieWidget);
	QLineEdit* titleInput = new QLineEdit(addMovieWidget);
	QLineEdit* genreInput = new QLineEdit(addMovieWidget);
	QLineEdit* yearInput = new QLineEdit(addMovieWidget);
	QLineEdit* likesInput = new QLineEdit(addMovieWidget);
	QLineEdit* trailerInput = new QLineEdit(addMovieWidget);
	addMovieConfirmButton = new QPushButton("Add Movie", addMovieWidget);
	addBackButton = new QPushButton("Back", addMovieWidget);

	addMovieLayout->addRow("Title:", titleInput);
	addMovieLayout->addRow("Genre:", genreInput);
	addMovieLayout->addRow("Year:", yearInput);
	addMovieLayout->addRow("Likes:", likesInput);
	addMovieLayout->addRow("Trailer Link:", trailerInput);
	addMovieLayout->addRow(addMovieConfirmButton);
	addMovieLayout->addRow(addBackButton);

	addMovieWidget->setLayout(addMovieLayout);
	addMovieWidget->hide();
	layout->addWidget(addMovieWidget);


	connect(addBackButton, &QPushButton::clicked, this, [this]() {
		addMovieWidget->hide();
		showAdminWidgets();
	});

	connect(addMovieConfirmButton, &QPushButton::clicked, this, [this, titleInput, genreInput, yearInput, likesInput, trailerInput]() {
		std::string title = titleInput->text().toStdString();
		std::string genre = genreInput->text().toStdString();
		int year = yearInput->text().toInt();
		int likes = likesInput->text().toInt();
		std::string trailer = trailerInput->text().toStdString();
		try {
			Movie m{ title, genre, year, likes, trailer };
			MovieValidator::validate(m);
			adminService.add_movie(title, genre, year, likes, trailer);
			undoStack.push_back(new AddMovieCommand(adminService, m));
			clearRedoStack();
			QMessageBox::information(this, "Success", "Movie added successfully!");
			populateMoviesTable();
			populateRemoveMovieList(removeMovieWidget->findChild<QListWidget*>());
			populateUpdateMovieList(titleComboBox);
		}
		catch (const ValidationException& e) {
			QMessageBox::warning(this, "Validation Error", QString::fromStdString(e.what()));
		}
		catch (const RepositoryException& e) {
			QMessageBox::warning(this, "Repository Error", QString::fromStdString(e.what()));
		}
	});
}

void AdminScreen::createRemoveMovieWidget() {
	removeMovieWidget = new QWidget(this);
	QVBoxLayout* removeMovieLayout = new QVBoxLayout(removeMovieWidget);
	QLabel* removeMovieLabel = new QLabel("Select a movie to remove:", removeMovieWidget);
	movieList = new QListWidget(removeMovieWidget);
	removeMovieConfirmButton = new QPushButton("Remove Movie", removeMovieWidget);
	removeMovieLayout->addWidget(removeMovieLabel);
	removeMovieLayout->addWidget(movieList);
	removeMovieLayout->addWidget(removeMovieConfirmButton);
	removeBackButton = new QPushButton("Back", removeMovieWidget);
	removeMovieLayout->addWidget(removeBackButton);
	removeMovieWidget->setLayout(removeMovieLayout);
	removeMovieWidget->hide();
	layout->addWidget(removeMovieWidget);

	std::vector<Movie> movies = adminService.get_movies();
	for (const auto& movie : movies) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(movie.get_title()));
		movieList->addItem(item);
	}

	connect(removeBackButton, &QPushButton::clicked, this, [this]() {
		removeMovieWidget->hide();
		showAdminWidgets();
	});

	connect(removeMovieConfirmButton, &QPushButton::clicked, this, [this]() {
		QListWidgetItem* selectedItem = movieList->currentItem();
		if (selectedItem) {
			std::string title = selectedItem->text().toStdString();
			try {
				Movie removedMovie;
				for (const auto& movie : adminService.get_movies()) {
					if (movie.get_title() == title) {
						removedMovie = movie;
						break;
					}
				}
				undoStack.push_back(new RemoveMovieCommand(adminService, removedMovie));
				clearRedoStack();
				adminService.remove_movie(title);
				QMessageBox::information(this, "Success", "Movie removed successfully!");
				delete selectedItem;
				populateRemoveMovieList(movieList);
				populateMoviesTable();
				populateUpdateMovieList(titleComboBox);
			}
			catch (const RepositoryException& e) {
				QMessageBox::warning(this, "Repository Error", QString::fromStdString(e.what()));
			}
		}
		else {
			QMessageBox::warning(this, "Selection Error", "Please select a movie to remove.");
		}
	});
}
void AdminScreen::createUpdateMovieWidget() {
	updateMovieWidget = new QWidget(this);
	QVBoxLayout* updateMovieLayout = new QVBoxLayout(updateMovieWidget);
	QLabel* updateMovieLabel = new QLabel("Select a movie to update:", updateMovieWidget);
	titleComboBox = new QComboBox(updateMovieWidget);
	std::vector<Movie> movies = adminService.get_movies();
	for (const auto& movie : movies) {
		titleComboBox->addItem(QString::fromStdString(movie.get_title()));
	}
	QLineEdit* genreInput = new QLineEdit(updateMovieWidget);
	QLineEdit* yearInput = new QLineEdit(updateMovieWidget);
	QLineEdit* likesInput = new QLineEdit(updateMovieWidget);
	QLineEdit* trailerInput = new QLineEdit(updateMovieWidget);
	updateMovieConfirmButton = new QPushButton("Update Movie", updateMovieWidget);
	updateBackButton = new QPushButton("Back", updateMovieWidget);
	updateMovieLayout->addWidget(updateMovieLabel);
	updateMovieLayout->addWidget(titleComboBox);
	updateMovieLayout->addWidget(new QLabel("New Genre:", updateMovieWidget));
	updateMovieLayout->addWidget(genreInput);
	updateMovieLayout->addWidget(new QLabel("New Year:", updateMovieWidget));
	updateMovieLayout->addWidget(yearInput);
	updateMovieLayout->addWidget(new QLabel("New Likes:", updateMovieWidget));
	updateMovieLayout->addWidget(likesInput);
	updateMovieLayout->addWidget(new QLabel("New Trailer Link:", updateMovieWidget));
	updateMovieLayout->addWidget(trailerInput);
	updateMovieLayout->addWidget(updateMovieConfirmButton);
	updateMovieLayout->addWidget(updateBackButton);
	updateMovieWidget->setLayout(updateMovieLayout);
	updateMovieWidget->hide();
	layout->addWidget(updateMovieWidget);

	connect(updateBackButton, &QPushButton::clicked, this, [this]() {
		updateMovieWidget->hide();
		showAdminWidgets();
		});

	connect(updateMovieConfirmButton, &QPushButton::clicked, this, [this, genreInput, yearInput, likesInput, trailerInput]() {
		std::string title = titleComboBox->currentText().toStdString();
		std::string genre = genreInput->text().toStdString();
		int year = yearInput->text().toInt();
		int likes = likesInput->text().toInt();
		std::string trailer = trailerInput->text().toStdString();
		try {
			Movie m{ title, genre, year, likes, trailer };
			MovieValidator::validate(m);
			Movie oldMovie;
			for (const auto& movie : adminService.get_movies()) {
				if (movie.get_title() == title) {
					oldMovie = movie;
					break;
				}
			}
			adminService.update_movie(title, genre, year, likes, trailer);
			undoStack.push_back(new UpdateMovieCommand(adminService, oldMovie, m));
			clearRedoStack();
			QMessageBox::information(this, "Success", "Movie updated successfully!");
			populateMoviesTable();
			populateUpdateMovieList(titleComboBox);
		}
		catch (const ValidationException& e) {
			QMessageBox::warning(this, "Validation Error", QString::fromStdString(e.what()));
		}
		catch (const RepositoryException& e) {
			QMessageBox::warning(this, "Repository Error", QString::fromStdString(e.what()));
		}
	});

}

void AdminScreen::createViewMoviesWidget() {
	viewMoviesWidget = new QWidget(this);

	moviesTableWidget = new QTableWidget(viewMoviesWidget);
	moviesTableWidget->setColumnCount(5);
	QStringList headers = { "Title", "Genre", "Year", "Likes", "Trailer" };
	moviesTableWidget->setHorizontalHeaderLabels(headers);
	moviesTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	moviesTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QVBoxLayout* viewMoviesLayout = new QVBoxLayout(viewMoviesWidget);
	QLabel* viewMoviesLabel = new QLabel("List of Movies:", viewMoviesWidget);

	viewMoviesBackButton = new QPushButton("Back", viewMoviesWidget);
	viewMoviesLayout->addWidget(viewMoviesLabel);
	viewMoviesLayout->addWidget(moviesTableWidget);
	viewMoviesLayout->addWidget(viewMoviesBackButton);
	viewMoviesWidget->setLayout(viewMoviesLayout);
	viewMoviesWidget->hide();
	layout->addWidget(viewMoviesWidget);

	std::vector<Movie> movies = adminService.get_movies();
	for (const auto& movie : movies) {
		QTableWidgetItem* titleItem = new QTableWidgetItem(QString::fromStdString(movie.get_title()));
		QTableWidgetItem* genreItem = new QTableWidgetItem(QString::fromStdString(movie.get_genre()));
		QTableWidgetItem* yearItem = new QTableWidgetItem(QString::number(movie.get_year()));
		QTableWidgetItem* likesItem = new QTableWidgetItem(QString::number(movie.get_likes()));
		QTableWidgetItem* trailerItem = new QTableWidgetItem(QString::fromStdString(movie.get_trailer()));
		int rowCount = moviesTableWidget->rowCount();
		moviesTableWidget->insertRow(rowCount);
		moviesTableWidget->setItem(rowCount, 0, titleItem);
		moviesTableWidget->setItem(rowCount, 1, genreItem);
		moviesTableWidget->setItem(rowCount, 2, yearItem);
		moviesTableWidget->setItem(rowCount, 3, likesItem);
		moviesTableWidget->setItem(rowCount, 4, trailerItem);
	}

	connect(viewMoviesBackButton, &QPushButton::clicked, this, [this]() {
		viewMoviesWidget->hide();
		showAdminWidgets();
		});

}

void AdminScreen::populateMoviesTable() {
	moviesTableWidget->setRowCount(0);
	std::vector<Movie> movies = adminService.get_movies();
	for (const auto& movie : movies) {
		int rowCount = moviesTableWidget->rowCount();
		moviesTableWidget->insertRow(rowCount);
		moviesTableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString(movie.get_title())));
		moviesTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString::fromStdString(movie.get_genre())));
		moviesTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(movie.get_year())));
		moviesTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString::number(movie.get_likes())));
		moviesTableWidget->setItem(rowCount, 4, new QTableWidgetItem(QString::fromStdString(movie.get_trailer())));
	}
}

void AdminScreen::populateRemoveMovieList(QListWidget* movieList) {
	movieList->clear();
	std::vector<Movie> movies = adminService.get_movies();
	for (const auto& movie : movies) {
		movieList->addItem(QString::fromStdString(movie.get_title()));
	}
}

void AdminScreen::populateUpdateMovieList(QComboBox* titleComboBox) {
	titleComboBox->clear();
	std::vector<Movie> movies = adminService.get_movies();
	for (const auto& movie : movies) {
		titleComboBox->addItem(QString::fromStdString(movie.get_title()));
	}
}

void AdminScreen::refreshMovies() {
	populateMoviesTable();
	populateUpdateMovieList(titleComboBox);
	populateRemoveMovieList(movieList);

}

void AdminScreen::undo() {
	if (!undoStack.empty()) {
		Command* command = undoStack.back();
		command->undo();
		redoStack.push_back(command);
		undoStack.pop_back();
		refreshMovies();
		QMessageBox::information(this, "Undo", "Last action undone successfully!");
	}
	else {
		QMessageBox::warning(this, "Undo Error", "No actions to undo.");
	}
}

void AdminScreen::redo() {
	if (!redoStack.empty()) {
		Command* command = redoStack.back();
		command->redo();
		undoStack.push_back(command);
		redoStack.pop_back();
		refreshMovies();
		QMessageBox::information(this, "Redo", "Last action redone successfully!");
	}
	else {
		QMessageBox::warning(this, "Redo Error", "No actions to redo.");
	}
}

void AdminScreen::clearRedoStack()
{
	for (Command* command : redoStack) {
		delete command;
	}
	redoStack.clear();
}