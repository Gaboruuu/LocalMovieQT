#pragma once

#include <string>
#include <vector>

class Movie {
public:
    Movie();
    Movie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);

    /**
     * @brief Gets the title of the movie.
     * @return The title of the movie.
     */
    std::string get_title() const;

    /**
     * @brief Gets the genre of the movie.
     * @return The genre of the movie.
     */
    std::string get_genre() const;

    /**
     * @brief Gets the release year of the movie.
     * @return The release year of the movie.
     */
    int get_year() const;

    /**
     * @brief Gets the number of likes the movie has.
     * @return The number of likes.
     */
    int get_likes() const;

    /**
     * @brief Gets the URL of the movie's trailer.
     * @return The URL of the trailer.
     */
    std::string get_trailer() const;

    /**
     * @brief Updates the details of the movie.
     * @param title The new title of the movie.
     * @param genre The new genre of the movie.
     * @param year The new release year of the movie.
     * @param likes The new number of likes the movie has.
     * @param trailer The new URL of the movie's trailer.
     */
    void update_movie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);

    /**
     * @brief Sets the number of likes for the movie.
     * @param likes The new number of likes.
     */
    void set_likes(int likes);

    /**
     * @brief Compares two movies based on their titles.
     * @param m The movie to compare with.
     * @return True if this movie's title is less than the other movie's title, false otherwise.
     */
    bool operator<(const Movie& m);

    /**
     * @brief Checks if two movies are equal based on their titles.
     * @param m The movie to compare with.
     * @return True if the movies have the same title, false otherwise.
     */
    bool operator==(const Movie& m);

    /**
     * @brief Converts the movie details to a string representation.
     * @return A string representation of the movie.
     */
    std::string to_string() const;

	/**
	* @brief Overloads the output stream operator to print movie details.
	* @param os The output stream.
    */
	friend std::ostream& operator<<(std::ostream& os, const Movie& m);
	
	/**
	* @brief Overloads the input stream operator to read movie details.
	* @param is The input stream.
    */
    friend std::istream& operator>>(std::istream& is, Movie& m);

private:
    std::string title;
    std::string genre;
    int year;
    int likes;
    std::string trailer;
};