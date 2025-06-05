#include "ServiceAdmin.h"
#include "Validate.h"
#include "RepoException.h"
#include "MovieValidater.h"
#include <iostream>


ServiceAdmin::ServiceAdmin(MovieRepository& repo) : repo{ repo }
{
}

ServiceAdmin::~ServiceAdmin()
{
}

void ServiceAdmin::add_movie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer)
{
	Movie m{ title, genre, year, likes, trailer };
	this->repo.add_movie(m);
}

void ServiceAdmin::remove_movie(const std::string& title)
{
	Movie m{ title, "", 0, 0, "" };
	this->repo.remove_movie(m);
}

void ServiceAdmin::update_movie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer)
{
	Movie m{ title, genre, year, likes, trailer };
	this->repo.update_movie(m);
}

std::vector<Movie> ServiceAdmin::get_movies() const{
	return this->repo.get_movies();
}


std::vector<Movie> ServiceAdmin::filter_likes(int likes) const {
	return repo.get_filtered_movies(likes);
}