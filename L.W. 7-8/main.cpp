#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "radio.hpp"

using namespace std;

// Функція для виводу меню користувача
void UserMenu();

// Функція для виводу інформації про радіо
void PrintRadioInfo(const FM_Radio& Phillips, const AM_Radio& Transistorola, int radioNum);

int main()
{
    // Створення об'єкта FM радіо
    FM_Radio Phillips;

    // Створення об'єкта AM радіо
    AM_Radio Transistorola;

    // Вибір об'єкта
    int radioNum;
    cout << "Select radio (0 - Phillips, 1 - Transistorola): ";
    cin >> radioNum;

    // Змінні для вибору та керування циклом
    int key;
    bool is_work = true;

    // Головний цикл програми
    do {
        // Виведення меню користувача
        UserMenu();

        // Виведення інформації про стан радіо
        PrintRadioInfo(Phillips, Transistorola, radioNum);

        // Очікування вибору користувача
        printf("Enter task code: ");
        cin >> key;

        // Обробка вибору користувача
        switch (key)
        {
            case 0:
                if (radioNum == 0)
                {
                    Phillips.TurnOff();
                    // Phillips = false;
                }
                else if (radioNum == 1)
                {
                    Transistorola.TurnOff();
                    // Transistorola = false;
                }              
                break;
            case 1:
                if (radioNum == 0)
                {
                    Phillips.TurnOn();
                    // Phillips = true;
                }
                else if (radioNum == 1)
                {
                    Transistorola.TurnOn();
                    // Transistorola = true;
                }
                break;
            case 2: 
                double frequency;
                cout << "Enter frequency (MHz): ";
                cin >> frequency;
                if (radioNum == 0)
                {
                    // Phillips.SetFrequency(frequency);
                    Phillips += frequency;
                }
                else if (radioNum == 1)
                {
                    // Transistorola.SetFrequency(frequency);
                    Transistorola += frequency;
                }
                break;
            case 3: 
                double volume;
                cout << "Enter volume (db): ";
                cin >> volume;
                if (radioNum == 0)
                {
                    // Phillips.SetVolume(volume);
                    Phillips -= volume;
                }
                else if (radioNum == 1)
                {
                    // Transistorola.SetVolume(volume);
                    Transistorola -= volume;
                }
                break;
            case 4:
                int index;
                double value;
                cout << "Enter index for saving this frequency: ";
                cin >> index;
                cout << "Enter frequency for saving: ";
                cin >> value;
                std::array<double, 2> value_and_index;
                value_and_index[0] = value;
                value_and_index[1] = index;
                if (radioNum == 0)
                {
                    // Phillips.SetInstalledFrequency(value_and_index);
                    Phillips << value_and_index;
                }
                else if (radioNum == 1)
                {
                    // Transistorola.SetInstalledFrequency(value_and_index);
                    Transistorola << value_and_index;
                }
                break;
            case 5:
                cout << "Select radio (0 - Phillips, 1 - Transistorola): ";
                cin >> radioNum;
                break;
            case 6: 
                Phillips.~FM_Radio();
                Phillips.~FM_Radio();
                Transistorola.~AM_Radio();
                Transistorola.~AM_Radio();
                cout << "All objects have been delated\n";
                is_work = false;
                break;
            case 7: 
                is_work = false;
                break;
            default: 
                cout << "Looks like you made a mistake" << endl;
                break;
        }
    } while (is_work == true);
    return 0;
}

// Виведення меню користувача
void UserMenu()
{
    system("clear");
    printf("-------------------------------------------------------------------\n");
    printf("--------------------Object-oriented radio model--------------------\n");
    printf("-------------------------------------------------------------------\n");
    printf("--------------------Select one of these options--------------------\n");
    printf("-------------------------------------------------------------------\n");
    printf("[0 - Turn off]\n");
    printf("[1 - Turn on]\n");
    printf("[2 - Set frequency]\n");
    printf("[3 - Set volume]\n");
    printf("[4 - Save frequency]\n");
    printf("[5 - Change object]\n");
    printf("[6 - Delate all objects]\n");
    printf("[7 - Exit]\n");
    printf("-------------------------------------------------------------------\n");
    printf("\n\n\n");
}

// Виведення інформації про стан радіо
void PrintRadioInfo(const FM_Radio& Phillips, const AM_Radio& Transistorola, int radioNum)
{
    if (radioNum == 0)
    {
        printf("-------------------------------------------------------------------\n");
        printf("-------------------------State of Phillips:------------------------\n");
        printf("-------------------------------------------------------------------\n");
        printf("Power: %d\n", Phillips.IsPoweredOn());
        printf("State: %s\n", Phillips.IsPoweredOn() ? "On" : "Off");
        printf("Volume: %.i Db\n", Phillips.GetIVolume());
        printf("Frequency: %.2f MHz\n", Phillips.GetFrequency());
        std::array<double, 5> frequencies = Phillips.GetInstalledFrequency();
        printf("Saved frequencies: %.2f MHz, %.2f MHz, %.2f MHz, %.2f MHz, %.2f MHz\n", frequencies[0], frequencies[1], frequencies[2], frequencies[3], frequencies[4]);
        printf("-------------------------------------------------------------------\n");
        printf("\n\n");
    }
    else if (radioNum == 1)
    {
        printf("-------------------------------------------------------------------\n");
        printf("----------------------State of Transistorola:----------------------\n");
        printf("-------------------------------------------------------------------\n");
        printf("Power: %d\n", Transistorola.IsPoweredOn());
        printf("State: %s\n", Transistorola.IsPoweredOn() ? "On" : "Off");
        printf("Volume: %.i Db\n", Transistorola.GetIVolume());
        printf("Frequency: %.2f MHz\n", Transistorola.GetFrequency());
        std::array<double, 5> frequencies = Transistorola.GetInstalledFrequency();
        printf("Saved frequencies: %.2f MHz, %.2f MHz, %.2f MHz, %.2f MHz, %.2f MHz\n", frequencies[0], frequencies[1], frequencies[2], frequencies[3], frequencies[4]);
        printf("-------------------------------------------------------------------\n");
        printf("\n\n");
    }
}