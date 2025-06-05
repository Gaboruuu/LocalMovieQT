#pragma once
#include "Domain.h"
#include <vector>

class MovieRepository {
public:
    MovieRepository(const std::string& file_path);
    ~MovieRepository();

    /**
     * @brief Adds a movie to the repository.
     * @param m The movie to add.
     */
    void add_movie(const Movie& m);

    /**
     * @brief Removes a movie from the repository.
     * @param m The movie to remove.
     */
    void remove_movie(const Movie& m);

    /**
     * @brief Updates the details of a movie in the repository.
     * @param m The movie with updated details.
     */
    void update_movie(const Movie& m);

    /**
     * @brief Increases the like count of a movie by its title.
     * @param title The title of the movie to like.
     */
    void like_movie(const std::string& title);

    /**
     * @brief Retrieves all movies from the repository.
     * @return A DynamicVector containing all movies in the repository.
     */
    std::vector<Movie> get_movies() const;

    /**
     * @brief Retrieves movies from the repository by genre.
     * @param genre The genre to filter movies by.
     * @return A DynamicVector containing movies of the specified genre.
     */
    std::vector<Movie> get_movies_by_genre(const std::string& genre) const;

    /**
     * @brief Retrieves a movie from the repository by its title.
     * @param title The title of the movie to retrieve.
     * @return A DynamicVector containing the movie with the specified title.
     */
    std::vector<Movie> get_movie_by_title(const std::string& title) const;

	/**
	 * @brief Retrieves movies from the repository with likes greater than or equal to a specified number.
	 * @param likes The minimum number of likes.
	 * @return A DynamicVector containing movies with likes greater than or equal to the specified number.
	 */
	std::vector<Movie> get_filtered_movies(int likes) const;

private:
	std::vector<Movie> repo;
	std::string file_path;

	/**
	 * @brief Loads movies from a file into the repository.
	 */
	void load_from_file();

	/**
	 * @brief Saves movies from the repository to a file.
	 */
	void save_to_file();
};