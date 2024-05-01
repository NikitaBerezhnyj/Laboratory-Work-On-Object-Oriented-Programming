#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// Функція для перевірки введення дробового числа
bool IsValidChar(const std::string &input);
// Функція для введення та перевірки дробового числа
char GetChar(const std::string &prompt);
// Функція для перевірки введення цілого числа
bool IsValidNumber(const std::string &input);
// Функція для введення та перевірки цілого числа
int GetNumber(const std::string &prompt);
// Функція для перевірки введення дробового числа
bool IsValidDouble(const std::string &input);
// Функція для введення та перевірки дробового числа
double GetDouble(const std::string &prompt);
// Виведення кольорових повідомлень
void SuccessMessage(std::string message);
void WarningMessage(std::string message);
void PanicMessage(std::string message);

#endif // UTILITY_HPP