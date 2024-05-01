#include "error.hpp"

UserInputException::UserInputException(const char *message) : msg(message) {}

const char *UserInputException::what() const noexcept
{
    return msg.c_str();
}

void UserInputException::waitForEnter() const
{
    std::cout << "Press Enter to continue... ";
    std::string tmp_str;
    std::getline(std::cin, tmp_str);
}