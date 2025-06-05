#include "MovieRepository.h"
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include "RepoException.h"


MovieRepository::MovieRepository(const std::string& file_path) : file_path(file_path) {
	load_from_file();
}


MovieRepository::~MovieRepository() {
	save_to_file();
}

void MovieRepository::add_movie(const Movie& m) {
	this->repo.push_back(m);
}

void MovieRepository::remove_movie(const Movie& m) {
	this->repo.erase(std::remove(this->repo.begin(), this->repo.end(), m), this->repo.end());
}

void MovieRepository::update_movie(const Movie& m) {
	for (int i = 0; i < this->repo.size(); i++) {
		if (this->repo[i].get_title() == m.get_title()) {
			this->repo[i] = m;
			return;
		}
	}
	throw RepositoryException("Element not found!");
}

std::vector<Movie> MovieRepository::get_movies() const {
	return this->repo;
}

std::vector<Movie> MovieRepository::get_movies_by_genre(const std::string& genre) const {
	std::vector<Movie> filtered_movies;
	for (const auto& m : this->repo) {
		if (m.get_genre() == genre) {
			filtered_movies.push_back(m);
		}
	}
	if (filtered_movies.empty()) {
		throw RepositoryException("No movies found in this genre");
	}

	return filtered_movies;
}

void MovieRepository::like_movie(const std::string& title) {
	for (int i = 0; i < this->repo.size(); i++) {
		if (this->repo[i].get_title() == title) {
			this->repo[i].set_likes(this->repo[i].get_likes() + 1);
			return;
		}
	}
	throw RepositoryException("Movie not found in repository");
}

std::vector<Movie> MovieRepository::get_movie_by_title(const std::string& title) const {
	std::vector<Movie> filtered_movies;
	for (const auto& m : this->repo) {
		if (m.get_title() == title) {
			filtered_movies.push_back(m);
		}
	}
	return filtered_movies;
}

std::vector<Movie> MovieRepository::get_filtered_movies(int likes) const {
	std::vector<Movie> filtered_movies;
	for (const auto& m : this->repo) {
		if (m.get_likes() >= likes) {
			filtered_movies.push_back(m);
		}
	}
	return filtered_movies;
}

void MovieRepository::load_from_file() {
	std::ifstream file(this->file_path);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file");
	}
	Movie movie;
	while (file >> movie) {
		this->repo.push_back(movie);
	}
	file.close();
}

void MovieRepository::save_to_file() {
	std::ofstream file(this->file_path);

	for (const auto& movie : this->repo) {
		file << movie << '\n';
	}
	file.close();
}

