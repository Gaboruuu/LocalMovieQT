#pragma once
#include <string>
#include <vector>
#include "Domain.h"
#include <cstdlib>

class WatchListViewer {
public:
	virtual ~WatchListViewer() = default;
	virtual void save(const std::vector<Movie>& movies, std::string filename) = 0;
	virtual void display(std::string filename) {
		std::string command = "start " + filename;
		system(command.c_str());
	}
};