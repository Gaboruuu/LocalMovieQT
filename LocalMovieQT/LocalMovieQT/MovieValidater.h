#pragma once
#include "Domain.h"
#include "Validate.h"

class MovieValidator {
public:
    static void validate(const Movie& movie) {
        if (movie.get_title().empty()) {
            throw ValidationException("Title cannot be empty.");
        }
        if (movie.get_genre().empty()) {
            throw ValidationException("Genre cannot be empty.");
        }
        if (movie.get_year() < 1888 || movie.get_year() > 2100) { // Movies started in 1888
            throw ValidationException("Year must be between 1888 and 2100.");
        }
        if (movie.get_likes() < 0) {
            throw ValidationException("Likes cannot be negative.");
        }
        if (movie.get_trailer().empty()) {
            throw ValidationException("Trailer URL cannot be empty.");
        }
    }
};