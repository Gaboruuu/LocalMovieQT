#include "ServiceUser.h"
#include <iostream>
#include <Windows.h>

std::vector<Movie> ServiceUser::get_movies() const {
	return this->repo.get_movies();
}

std::vector<Movie> ServiceUser::get_movies_by_genre(const std::string& genre) const {
	return this->repo.get_movies_by_genre(genre);
}

void ServiceUser::add_movie_to_watchlist(const std::string& title) {
	if (this->watchlist.get_movie_by_title(title).get_title() != "")
		throw std::exception("Movie already in watchlist!");
	this->watchlist.add_movie(this->repo.get_movie_by_title(title)[0]);
	this->csv_viewer.save(this->watchlist.get_movies(), "WatchlistCSV.csv");
	this->html_viewer.save(this->watchlist.get_movies(), "WatchlistHTML.html");
}

std::vector<Movie> ServiceUser::get_watchlist() const {
	return this->watchlist.get_movies();
}

void ServiceUser::play_trailer(const std::string& trailer) {
	//ShellExecuteA(0, 0, trailer.c_str(), 0, 0, SW_SHOW);
}

void ServiceUser::like_movie(const std::string& title) {
	this->repo.like_movie(title);
}

void ServiceUser::remove_movie_from_watchlist(const std::string& title) {
	this->watchlist.remove_movie(this->repo.get_movie_by_title(title)[0]);
	this->csv_viewer.save(this->watchlist.get_movies(), "WatchlistCSV.csv");
	this->html_viewer.save(this->watchlist.get_movies(), "WatchlistHTML.html");	
}

void ServiceUser::display_watchlist(std::string format) {
	if (format == "csv") {
		this->csv_viewer.display("WatchlistCSV.csv");
	}
	else if (format == "html") {
		this->html_viewer.display("WatchlistHTML.html");
	}
	else {
		throw std::exception("Invalid format!");
	}
}