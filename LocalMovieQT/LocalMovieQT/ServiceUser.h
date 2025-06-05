#pragma once
#include "WatchListRepository.h"
#include "MovieRepository.h"
#include "CSVWatchListViewer.h"
#include "HTMLWatchListViewer.h"


class ServiceUser {
public:
    ServiceUser(MovieRepository& repo, WatchListRepository& watchlist) : repo{ repo }, watchlist{ watchlist } {
		this->csv_viewer.save(this->watchlist.get_movies(), "WatchlistCSV.csv");
		this->html_viewer.save(this->watchlist.get_movies(), "WatchlistHTML.html");
    }
    ~ServiceUser() {}

    /**
     * @brief Adds a movie to the watchlist by its title.
     * @param title The title of the movie to add.
     */
    void add_movie_to_watchlist(const std::string& title);

    /**
     * @brief Removes a movie from the watchlist by its title.
     * @param title The title of the movie to remove.
     */
    void remove_movie_from_watchlist(const std::string& title);

    /**
     * @brief Retrieves the current watchlist.
     * @return A DynamicVector containing the movies in the watchlist.
     */
    std::vector<Movie> get_watchlist() const;

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
     * @brief Plays the trailer of a movie by its title.
     * @param title The title of the movie whose trailer to play.
     */
    void play_trailer(const std::string& title);

    /**
     * @brief Likes a movie by its title, increasing its like count.
     * @param title The title of the movie to like.
     */
    void like_movie(const std::string& title);

    void display_watchlist(std::string format);

private:
    MovieRepository& repo;
    WatchListRepository& watchlist;
	CSVWatchListViewer csv_viewer;
	HTMLWatchListViewer html_viewer;
};
