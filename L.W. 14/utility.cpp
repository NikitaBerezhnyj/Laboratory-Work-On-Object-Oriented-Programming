#include "utility.hpp"

// Перевірка правильності введеного символу
bool IsValidChar(const std::string &input)
{
    return !input.empty() && input == "y" || input == "n";
}

// Введення символу користувачем
char GetChar(const std::string &prompt)
{
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);

    if (IsValidChar(input))
    {
        if (input.length() != 1)
        {
            return ' ';
        }
        return input[0];
    }
    else
    {
        return ' ';
    }
}

// Валідація введеного цілого числа
bool IsValidNumber(const std::string &input)
{
    return !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);
}

// Введення та перевірка цілого числа
int GetNumber(const std::string &prompt)
{
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);

    if (IsValidNumber(input))
    {
        return std::stoi(input);
    }
    else
    {
        return -1;
    }
}

// Валідація введеного дробового числа
bool IsValidDouble(const std::string &input)
{
    return !input.empty() && std::all_of(input.begin(), input.end(), [](char c)
                                         { return std::isdigit(c) || c == '.' || c == '-'; });
}

// Введення та перевірка дробового числа
double GetDouble(const std::string &prompt)
{
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);

    if (IsValidDouble(input))
    {
        return std::stod(input);
    }
    else
    {
        return -1;
    }
}

// Повідомлення про успішне виконання
void SuccessMessage(std::string message)
{
    cout << "\e[0;32m" << message << "\e[0m" << endl;
}

// Попередження про помилку
void WarningMessage(std::string message)
{
    cout << "\e[0;33m" << message << "\e[0m" << endl;
}

// Повідомлення про критичну помилку
void PanicMessage(std::string message)
{
    cout << "\e[0;31m" << message << "\e[0m" << endl;
}