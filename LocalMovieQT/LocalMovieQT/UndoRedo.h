#pragma once
#include "ServiceAdmin.h"

class Command {
public:
    virtual ~Command() {}
    virtual void undo() = 0;
    virtual void redo() = 0;
};

class AddMovieCommand : public Command {
    ServiceAdmin& service;
    Movie movie;
public:
    AddMovieCommand(ServiceAdmin& s, const Movie& m) : service(s), movie(m) {}
    void undo() override { service.remove_movie(movie.get_title()); }
    void redo() override { service.add_movie(movie.get_title(), movie.get_genre(), movie.get_year(), movie.get_likes(), movie.get_trailer()); }
};

class RemoveMovieCommand : public Command {
    ServiceAdmin& service;
    Movie movie;
public:
    RemoveMovieCommand(ServiceAdmin& s, const Movie& m) : service(s), movie(m) {}
    void undo() override { service.add_movie(movie.get_title(), movie.get_genre(), movie.get_year(), movie.get_likes(), movie.get_trailer()); }
    void redo() override { service.remove_movie(movie.get_title()); }
};

class UpdateMovieCommand : public Command {
    ServiceAdmin& service;
    Movie oldMovie, newMovie;
public:
    UpdateMovieCommand(ServiceAdmin& s, const Movie& oldM, const Movie& newM) : service(s), oldMovie(oldM), newMovie(newM) {}
    void undo() override { service.update_movie(oldMovie.get_title(), oldMovie.get_genre(), oldMovie.get_year(), oldMovie.get_likes(), oldMovie.get_trailer()); }
    void redo() override { service.update_movie(newMovie.get_title(), newMovie.get_genre(), newMovie.get_year(), newMovie.get_likes(), newMovie.get_trailer()); }
};