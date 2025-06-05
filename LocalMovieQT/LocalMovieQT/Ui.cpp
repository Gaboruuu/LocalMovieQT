#include "Ui.h"
#include <iostream>
#include <vector>
#include <string>

void Ui::run() {

	while (1) {
		system("cls");
		print_welcome();
		std::string command;
		std::cout << "Enter the command: ";
		std::cin >> command;
		if (command == "exit")
			break;

		if (command == "admin")
		{
			admin_commands();

		}
		else if (command == "user") {
			user_commands();
		}

		else {
			std::cout << "Invalid command!\n";
			system("pause");
		}
		std::system("pause");
	}
}

void Ui::user_commands()
{
	while (1) {
		system("cls");
		print_user_commands();
		std::string command3 = "";
		std::cout << "Enter the command: ";	
		std::cin >> command3;
		if (command3 == "exit")
			break;

		if (command3 == "list") {
			user_list();
		}

		else if (command3 == "wlist") {
			std::vector<Movie> movies = this->user.get_watchlist();
			for (Movie movie : movies) {
				std::cout << movie.to_string() << '\n';
			}
		}

		else if (command3 == "remove") {
			std::string title;
			std::cout << "Enter the title: ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, title);
			try {
				this->user.remove_movie_from_watchlist(title);
			}
			catch (std::exception& e) {
				std::cout << e.what() << "\n";
				std::cout << "\n";
				system("pause");
				continue;
			}
			std::cout << "Movie removed successfully!\n";
		}

		else if (command3 == "display") {
			std::string format;
			std::cout << "Enter the format (csv/html): ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, format);
			try {
				this->user.display_watchlist(format);
			}
			catch (std::exception& e) {
				std::cout << e.what() << "\n";
				std::cout << "\n";
				system("pause");
				continue;
			}
		}

		else {
			std::cout << "Invalid command!\n";
		}

		std::cout << "\n";
		system("pause");

	}
}

void Ui::user_list() {
	std::string genre;
	std::cout << "Enter the genre: ";
	while (std::cin.get() != '\n');
	std::getline(std::cin, genre);
	if (genre != "")
	{
		std::vector<Movie> movies;
		try {
			movies = this->user.get_movies_by_genre(genre);
		}
		catch (std::exception& e) {
			std::cout << e.what() << "\n";
			std::cout << "\n";
			system("pause");
			return;
		}

		std::string cmd;;
		int i = 0;
		while (true)
		{
			if (i >= movies.size())
				i = 0;
			std::cout << movies[1].to_string() << "\n";
			this->user.play_trailer(movies[i].get_trailer());
			std::cout << "Did you liked the trailer(y/n)";
			std::string answer;
			std::cin >> answer;
			if (answer == "y")
			{
				this->user.like_movie(movies[i].get_title());
				std::cout << "Movie liked!\n\n";
			}
			else if (answer == "n")
			{
				std::cout << "Movie not liked!\n\n";
			}
			else {
				std::cout << "Invalid command!\n";
			}
			std::cout << "Do you want to add this movie to your watchlist(y/n)";
			std::string answer2;
			std::cin >> answer2;
			if (answer2 == "y")
			{
				try {
					this->user.add_movie_to_watchlist(movies[i].get_title());
					std::cout << "Movie added to watchlist!\n\n";
				}
				catch (std::exception e) {
					std::cout << e.what() << '\n';
				}
			}
			else if (answer2 == "n")
			{
				std::cout << "Movie not added to watchlist!\n\n";
			}
			else {
				std::cout << "Invalid command!\n";
			}
			std::cout << "Continue? (y/n)";
			std::cin >> cmd;

			if (cmd == "n")
				break;
			else if (cmd != "y")
			{
				std::cout << "Invalid command!\n";
				break;
			}
			i++;
		}
	}
	else
	{
		std::vector<Movie> movies = this->user.get_movies();
		std::string cmd;
		int i = 0;
		while (true)
		{
			if (i >= movies.size())
				i = 0;

			std::cout << movies[i].to_string() << "\n";
			this->user.play_trailer(movies[i].get_trailer());
			std::cout << "Did you liked the trailer(y/n)";
			std::string answer;
			std::cin >> answer;
			if (answer == "y")
			{
				this->user.like_movie(movies[i].get_title());
				std::cout << "Movie liked!\n\n";
			}
			else if (answer == "n")
			{
				std::cout << "Movie not liked!\n\n";
			}
			else {
				std::cout << "Invalid command!\n";
			}
			std::cout << "Do you want to add this movie to your watchlist(y/n)";
			std::string answer2;
			std::cin >> answer2;
			if (answer2 == "y")
			{
				try {
					this->user.add_movie_to_watchlist(movies[i].get_title());
				}
				catch (std::exception& e) {
					std::cout << e.what() << "\n";
				}
				std::cout << "Movie added to watchlist!\n\n";
			}
			else if (answer2 == "n")
			{
				std::cout << "Movie not added to watchlist!\n\n";
			}
			else {
				std::cout << "Invalid command!\n";
			}
			std::cout << "Continue? (y/n)";
			std::cin >> cmd;

			if (cmd == "n")
				break;
			else if (cmd != "y")
			{
				std::cout << "Invalid command!\n";
				break;
			}
			i++;
		}
	}
}

void Ui::admin_commands()
{
	while (1) {
		system("cls");
		print_admin_commands();
		std::string command2 = "";
		std::cout << "Enter the command: ";
		std::cin >> command2;
		if (command2 == "exit")
			break;

		if (command2 == "add") {
			std::string title, genre, trailer;
			int year, likes;
			std::cout << "Enter the title: ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, title);
			std::cout << "Enter the genre: ";
			std::cin >> genre;
			std::cout << "Enter the year: ";
			std::cin >> year;
			std::cout << "Enter the number of likes: ";
			std::cin >> likes;
			std::cout << "Enter the trailer: ";
			std::cin >> trailer;
			try {
				this->admin.add_movie(title, genre, year, likes, trailer);

			}
			catch (std::exception& e) {
				std::cout << e.what() << "\n";
				std::cout << "\n";
				system("pause");
				continue;
			}
			
			
		}

		if (command2 == "remove") {
			std::string title;
			std::cout << "Enter the title: ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, title);
			try {
				this->admin.remove_movie(title);
			}
			catch (std::exception& e) {
				std::cout << e.what() << "\n";
				std::cout << "\n";
				system("pause");
				continue;
			}
			std::cout << "Movie removed successfully!\n";
		}

		if (command2 == "update") {
			std::string title, genre, trailer;
			int year, likes;
			std::cout << "Enter the title: ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, title);
			std::cout << "Enter the genre: ";
			std::cin >> genre;
			std::cout << "Enter the year: ";
			std::cin >> year;
			std::cout << "Enter the number of likes: ";
			std::cin >> likes;
			std::cout << "Enter the trailer: ";
			std::cin >> trailer;
			try {
				this->admin.update_movie(title, genre, year, likes, trailer);
			}
			catch (std::exception& e) {
				std::cout << e.what() << "\n";
				std::cout << "\n";
				system("pause");
				continue;
			}
			std::cout << "Movie updated successfully!\n";
		}

		if (command2 == "list") {
			std::vector<Movie> movies = this->admin.get_movies();
			for (Movie movie : movies) {
				std::cout << movie.to_string() << '\n';
			}
		}

		if (command2 == "filter") {
			int likes = 0;
			std::cout << "The Minimum of likes: ";
			std::cin >> likes;
			std::vector<Movie> movies = this->admin.filter_likes(likes);
			for (Movie movie : movies) {
				std::cout << movie.to_string() << '\n';
			}
		}

		std::cout << "\n";
		system("pause");

	}
}

void Ui::print_welcome(){
	std::cout << "Welcome to the Local Movie Database!\n";
	std::cout << "Please enter one of the following commands:\n";
	std::cout << "admin - to enter the admin mode\n";
	std::cout << "user - to enter the user mode\n";
	std::cout << "exit - to exit the application\n";
}

void Ui::print_admin_commands() {
	std::cout << "You are now in the admin mode. Please enter one of the following commands:\n";
	std::cout << "add - to add a movie to the database\n";
	std::cout << "remove - to remove a movie from the database\n";
	std::cout << "update - to update a movie from the database\n";
	std::cout << "list - to list all the movies in the database\n";
	std::cout << "filer - show movies with more then x likes\n";
	std::cout << "exit - to exit the admin mode\n";
}

void Ui::print_user_commands() {

	std::cout << "You are now in the user mode. Please enter one of the following commands:\n";
	std::cout << "list - to list all the movies in the database by geanre or all if null\n";
	std::cout << "wlist - to list all the movies in your watch list\n";
	std::cout << "remove - to remove a movie from your watch list\n";
	std::cout << "display - to display the watch list in a specific format (csv or html)\n";
	std::cout << "exit - to exit the user mode\n";
}