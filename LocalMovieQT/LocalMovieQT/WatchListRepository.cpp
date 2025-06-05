#include "WatchListRepository.h"
#include <algorithm>
#include <stdexcept>
#include <fstream>

WatchListRepository::WatchListRepository(const std::string& file_path) : file_path(file_path) {
	load_from_file();
}


WatchListRepository::~WatchListRepository(){
	save_to_file();
}

void WatchListRepository::add_movie(const Movie& m)
{
	this->repo.push_back(m);
}

void WatchListRepository::remove_movie(const Movie& m){
	this->repo.erase(std::remove(this->repo.begin(), this->repo.end(), m), this->repo.end());
}

std::vector<Movie> WatchListRepository::get_movies() const{
	return this->repo;
}

Movie WatchListRepository::get_movie_by_title(const std::string& title) const{
	std::vector<Movie> movies = this->repo;
	for (const auto& m : movies) {
		if (m.get_title() == title) {
			return m;
		}
	}

	return Movie();
}

void WatchListRepository::load_from_file() {
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

void WatchListRepository::save_to_file() {
	std::ofstream file(this->file_path);

	for (const auto& m : this->repo) {
		file << m.get_title() << "," << m.get_genre() << "," << m.get_year() << "," << m.get_likes() << "," << m.get_trailer() << "\n";
	}
	file.close();
}