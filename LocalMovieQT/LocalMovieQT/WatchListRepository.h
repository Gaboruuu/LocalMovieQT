#pragma once

#include "Domain.h"
#include <vector>

class WatchListRepository {
public:
    WatchListRepository(const std::string& file_path);
    ~WatchListRepository();

    /**
     * @brief Adds a movie to the watchlist repository.
     * @param m The movie to add.
     */
    void add_movie(const Movie& m);

    /**
     * @brief Removes a movie from the watchlist repository.
     * @param m The movie to remove.
     */
    void remove_movie(const Movie& m);

    /**
     * @brief Retrieves all movies from the watchlist repository.
     * @return A DynamicVector containing all movies in the watchlist repository.
     */
    std::vector<Movie> get_movies() const;

    /**
     * @brief Retrieves a movie from the watchlist repository by its title.
     * @param title The title of the movie to retrieve.
     * @return The movie with the specified title.
     */
    Movie get_movie_by_title(const std::string& title) const;

private:
    std::vector<Movie> repo;
	std::string file_path;
	void load_from_file();
	void save_to_file();
};