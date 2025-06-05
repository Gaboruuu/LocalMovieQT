#pragma once
#include <string>
#include "WatchListViewer.h"
#include <fstream>

class HTMLWatchListViewer : public WatchListViewer {
public:
	void save(const std::vector<Movie>& movies, std::string filename) override {
		std::ofstream file(filename);
		file << "<html>\n";
		file << "<head><title>Watchlist</title></head>\n";
		file << "<body>\n";
		file << "<h1>Watchlist</h1>\n";
		file << "<table border=\"1\">\n";
		file << "<tr><th>Title</th><th>Genre</th><th>Year</th><th>Likes</th><th>Trailer</th></tr>\n";
		for (const auto& movie : movies) {
			file << "<tr>";
			file << "<td>" << movie.get_title() << "</td>";
			file << "<td>" << movie.get_genre() << "</td>";
			file << "<td>" << movie.get_year() << "</td>";
			file << "<td>" << movie.get_likes() << "</td>";
			file << "<td><a href=\"" << movie.get_trailer() << "\">Watch Trailer</a></td>";
			file << "</tr>\n";
		}
		file << "</table>\n";
		file << "</body>\n";
		file << "</html>\n";
	}
};