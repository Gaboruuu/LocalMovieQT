#pragma once

#include "MovieRepository.h"
#include <vector>

class ServiceAdmin {
public:
    ServiceAdmin(MovieRepository& repo);
    ~ServiceAdmin();

    /**
     * @brief Adds a movie to the repository.
     * @param title The title of the movie.
     * @param genre The genre of the movie.
     * @param year The release year of the movie.
     * @param likes The number of likes the movie has.
     * @param trailer The URL of the movie's trailer.
     */
    void add_movie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);

    /**
     * @brief Removes a movie from the repository by its title.
     * @param title The title of the movie to remove.
     */
    void remove_movie(const std::string& title);

    /**
     * @brief Updates the details of a movie in the repository.
     * @param title The title of the movie.
     * @param genre The genre of the movie.
     * @param year The release year of the movie.
     * @param likes The number of likes the movie has.
     * @param trailer The URL of the movie's trailer.
     */
    void update_movie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);

    /**
     * @brief Retrieves all movies from the repository.
     * @return A DynamicVector containing all movies in the repository.
     */
    std::vector<Movie> get_movies() const;

	/**
	 * @brief Filters movies based on the number of likes.
	 * @param likes The minimum number of likes.
	 * @return A DynamicVector containing movies with likes greater than or equal to the specified number.
	 */
    std::vector<Movie> filter_likes(int likes) const;

private:
    MovieRepository& repo;
};
