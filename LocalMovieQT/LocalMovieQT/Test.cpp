#include "Test.h"

void test_movie() {
	Movie movie("Title", "Genre", 2021, 100, "trailer");
	assert(movie.get_title() == "Title");
	assert(movie.get_genre() == "Genre");
	assert(movie.get_year() == 2021);
	assert(movie.get_likes() == 100);
	assert(movie.get_trailer() == "trailer");
	movie.set_likes(200);
	assert(movie.get_likes() == 200);
	movie.update_movie("NewTitle", "NewGenre", 2022, 300, "new_trailer");
	assert(movie.get_title() == "NewTitle");

	//Test operator<
	Movie movie2("Title2", "Genre2", 2021, 100, "trailer");
	assert(movie < movie2 == true);

	//Test to_string
	std::string str = movie.to_string();
	assert(str == "NewTitle | NewGenre | 2022 | 300 likes | new_trailer");
}

void test_service_user() {
	MovieRepository movieRepo("test_movies.txt");
	WatchListRepository watchlistRepo("test_wlist.txt");
	ServiceUser serviceUser(movieRepo, watchlistRepo);

	try {
		MovieRepository emptyRepo("empty.txt");
	}
	catch (std::exception& e) {
		std::string s = e.what();
		assert(s == "Could not open file");
	}

	try {
		WatchListRepository emptyRepo("empty.txt");
	}
	catch (std::exception& e) {
		std::string s = e.what();
		assert(s == "Could not open file");
	}

	// Test get_movies
	std::vector<Movie> movies = serviceUser.get_movies();
	assert(movies.size() == 0);

	// Add a movie to the repository for further tests
	movieRepo.add_movie(Movie("Title1", "Genre1", 2021, 100, "trailer1"));

	// Test add_movie_to_watchlist
	serviceUser.add_movie_to_watchlist("Title1");
	std::vector<Movie> watchlist = serviceUser.get_watchlist();
	assert(watchlist.size() == 1);

	try {
		serviceUser.add_movie_to_watchlist("Title1");
	}
	catch (std::exception& e) {
		std::string s = e.what();
		assert(s == "Movie already in watchlist!");
	}

	// Test remove_movie_from_watchlist
	serviceUser.remove_movie_from_watchlist("Title1");
	watchlist = serviceUser.get_watchlist();
	assert(watchlist.size() == 0);

	// Test play_trailer
	serviceUser.play_trailer("trailer1"); // Uncomment to test playing the trailer
	
	// Test like_movie

	serviceUser.like_movie("Title1");
	movies = movieRepo.get_movies();
	assert(movies[0].get_likes() == 101);

	try {
		serviceUser.like_movie("NonExistentMovie");
	}
	catch (std::exception& e) {
		std::string s = e.what();
		assert(s == "Movie not found in repository");
	}

	// Test get_movies_by_genre
	std::vector<Movie> filteredMovies = serviceUser.get_movies_by_genre("Genre1");
	assert(filteredMovies.size() == 1);
	assert(filteredMovies[0].get_title() == "Title1");

	try {
		serviceUser.get_movies_by_genre("NonExistentGenre");
	}
	catch (std::exception& e) {
		std::string s = e.what();
		assert(s == "No movies found in this genre");
	}

	// Test get_movie_by_title
	watchlistRepo.add_movie(Movie("Title1", "Genre1", 2021, 100, "trailer1"));
	assert(watchlistRepo.get_movie_by_title("Title1").get_title() == "Title1");


	watchlistRepo.remove_movie(Movie("Title1", "Genre1", 2021, 100, "trailer1"));
	movieRepo.remove_movie(Movie("Title1", "Genre1", 2021, 100, "trailer1"));
}


void test_service_admin() {
	MovieRepository movieRepo("test_movies.txt");
	ServiceAdmin serviceAdmin(movieRepo);

	// Test add_movie
	serviceAdmin.add_movie("Title1", "Genre1", 2021, 100, "trailer1");
	std::vector<Movie> movies = serviceAdmin.get_movies();
	assert(movies.size() == 1);
	assert(movies[0].get_title() == "Title1");
	
	try {
		serviceAdmin.add_movie("", "Genre1", 2021, 100, "trailer1");
	}
	catch (std::exception& e) {
		std::string s = e.what();
		assert(s == "Invalid movie data!");
	}


	// Test remove_movie
	serviceAdmin.add_movie("Title2", "Genre1", 2021, 200, "trailer1");
	serviceAdmin.remove_movie("Title1");
	movies = serviceAdmin.get_movies();
	assert(movies.size() == 1);

	serviceAdmin.remove_movie("Title2");


	// Test update_movie
	serviceAdmin.add_movie("Title1", "Genre1", 2021, 100, "trailer1");
	serviceAdmin.update_movie("Title1", "Genre2", 2022, 200, "trailer2");
	try {
		serviceAdmin.update_movie("Title2", "Genre2", 2022, 200, "trailer2");
	}
	catch (std::exception& e) {
		std::string s = e.what();
		assert(s == "Element not found!");
	}



	movies = serviceAdmin.get_movies();
	assert(movies.size() == 1);
	assert(movies[0].get_title() == "Title1");
	assert(movies[0].get_genre() == "Genre2");
	assert(movies[0].get_year() == 2022);
	assert(movies[0].get_likes() == 200);
	assert(movies[0].get_trailer() == "trailer2");

	// Test Filter Likes  
	serviceAdmin.add_movie("Title2", "Genre1", 2021, 200, "trailer1");
	std::vector<Movie> filteredMovies = serviceAdmin.filter_likes(100);
	assert(filteredMovies.size() == 2);
	assert(filteredMovies[0].get_title() == "Title1");


	// Clean up test files
	serviceAdmin.remove_movie("Title1");
	serviceAdmin.remove_movie("Title2");
}