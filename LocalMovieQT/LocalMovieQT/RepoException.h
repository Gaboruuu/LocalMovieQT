#pragma once
#include <stdexcept>
#include <string>

class RepositoryException : public std::runtime_error {
public:
    explicit RepositoryException(const std::string& message) : std::runtime_error(message) {}
};