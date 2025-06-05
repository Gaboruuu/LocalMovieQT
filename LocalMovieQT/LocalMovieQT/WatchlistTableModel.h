#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "Domain.h"

class WatchlistTableModel : public QAbstractTableModel {
	Q_OBJECT
	std::vector<Movie> movies;
public:
	WatchlistTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}
	void setMovies(const std::vector<Movie>& newMovies) {
		beginResetModel();
		movies = newMovies;
		endResetModel();
	}
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return movies.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5; // Title, Genre, Year, Likes, Trailer
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (!index.isValid() || index.row() < 0 || index.row() >= movies.size())
			return QVariant();
		const Movie& movie = movies[index.row()];
		if (role == Qt::DisplayRole) {
			switch (index.column()) {
			case 0: return QString::fromStdString(movie.get_title());
			case 1: return QString::fromStdString(movie.get_genre());
			case 2: return movie.get_year();
			case 3: return movie.get_likes();
			case 4: return QString::fromStdString(movie.get_trailer());
			default: return QVariant();
			}
		}
		return QVariant();
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			if (orientation == Qt::Horizontal) {
				switch (section) {
				case 0: return QString("Title");
				case 1: return QString("Genre");
				case 2: return QString("Year");
				case 3: return QString("Likes");
				case 4: return QString("Trailer");
				default: return QVariant();
				}
			}
		}
		return QVariant();
	}
};
