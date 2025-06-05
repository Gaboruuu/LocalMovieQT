#include "Domain.h"
#include <iostream>
#include <string>
#include <sstream>

Movie::Movie() = default;

Movie::Movie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer) {
	this->title = title;
	this->genre = genre;
	this->year = year;
	this->likes = likes;
	this->trailer = trailer;
}

std::string Movie::get_title() const {
	return title;
}

std::string Movie::get_genre() const {
	return genre;
}

int Movie::get_year() const {
	return year;
}

int Movie::get_likes() const {
	return likes;
}

std::string Movie::get_trailer() const {
	return trailer;
}

void Movie::set_likes(int likes) {
	this->likes = likes;
}

void Movie::update_movie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer) {
	this->title = title;
	this->genre = genre;
	this->year = year;
	this->likes = likes;
	this->trailer = trailer;
}

bool Movie::operator==(const Movie& other) {
	return title == other.title;
}

bool Movie::operator < (const Movie& other) {
	return title < other.title;
}


std::string Movie::to_string() const{
	return title + " | " + genre + " | " + std::to_string(year) + " | " + std::to_string(likes) + " likes | " + trailer;
}

std::ostream& operator<<(std::ostream& os, const Movie& m) {
	os << m.title << "," << m.genre << "," << m.year << "," << m.likes << "," << m.trailer;
	return os;
}

std::istream& operator>>(std::istream& is, Movie& m) {
	std::string line;
	if (std::getline(is, line)) {
		std::stringstream ss(line);
		std::getline(ss, m.title, ',');
		std::getline(ss, m.genre, ',');
		ss >> m.year;
		ss.ignore(1);
		ss >> m.likes;
		ss.ignore(1);
		std::getline(ss, m.trailer);
	}
	return is;
}