#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <iostream>
#include <exception>
#include <stdexcept>

class UserInputException : public std::exception
{
public:
    explicit UserInputException(const char *message);
    const char *what() const noexcept override;
    void waitForEnter() const;

private:
    std::string msg;
};

#endif // ERROR_HPP