#pragma once
#include <string>
#include "WatchListViewer.h"
#include <fstream>

class CSVWatchListViewer : public WatchListViewer {
public:
	void save(const std::vector<Movie>& movies, std::string filename) override {
        std::ofstream file(filename);
        for (const auto& movie : movies) {
            file << movie << "\n";
        }
        file.close();
	}
};