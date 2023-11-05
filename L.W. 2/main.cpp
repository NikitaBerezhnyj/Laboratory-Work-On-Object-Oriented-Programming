#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "radio.hpp"

using namespace std;

// Функція для виводу меню користувача
void UserMenu();

// Функція для виводу інформації про радіо
void PrintRadioInfo(const Radio& radio);

int main()
{
    // Створення об'єкта радіо та ініціалізація
    // Конструктор за замовчуванням
    Radio Boombox;
    Boombox.Reset();

    // Конструктор ініціалізації
    Radio Walkman(true, 98.5, 50.0, RadioRange::FM_Medium, 90.0, 75.0, 95.0, 50, RadioPort::FM, RadioAntenna::Yagi);

    // Конструктор копіювання
    // Radio Panasonic = Walkman;
    Radio Panasonic(Walkman);

    // Змінні для вибору та керування циклом
    int key;
    bool is_work = true;

    // Головний цикл програми
    do {
        // Виведення меню користувача
        UserMenu();

        // Виведення інформації про стан радіо
        PrintRadioInfo(Boombox);

        // Очікування вибору користувача
        printf("Enter task code: ");
        cin >> key;

        // Обробка вибору користувача
        switch (key)
        {
            case 0:
                Boombox.TurnOff();
                break;
            case 1:
                Boombox.TurnOn();
                break;
            case 2: 
                double frequency;
                cout << "Enter frequency (MHz): ";
                cin >> frequency;
                Boombox.SetFrequency(frequency);
                break;
            case 3: 
                float outputPower;
                cout << "Enter output power (W): ";
                cin >> outputPower;
                Boombox.SetOutputPower(outputPower);
                break;
            case 4:
                int range;
                cout << "Select range (0 - FM_Short, 1 - FM_Medium, 2 - FM_Long, 3 - AM_Short, 4 - AM_Medium, 5 - AM_Long, 6 - SW, 7 - LW): ";
                cin >> range;
                Boombox.SetRange(static_cast<RadioRange>(range));
                break;
            case 5: 
                float sensitivity;
                cout << "Enter sensitivity (dBm): ";
                cin >> sensitivity;
                Boombox.SetSensitivity(sensitivity);
                break;
            case 6: 
                float impedance;
                cout << "Enter impedance (ohm): ";
                cin >> impedance;
                Boombox.SetImpedance(impedance);
                break;
            case 7: 
                float snr;
                cout << "Enter signal-to-noise ratio (dB): ";
                cin >> snr;
                Boombox.SetSignalToNoiseRatio(snr);
                break;
            case 8: 
                int numChannels;
                cout << "Enter number of channels: ";
                cin >> numChannels;
                Boombox.SetNumberOfChannels(numChannels);
                break;
            case 9: 
                int ports;
                cout << "Select ports (0 - AM, 1 - FM, 2 - SW, 3 - LW): ";
                cin >> ports;
                Boombox.SetPorts(static_cast<RadioPort>(ports));
                break;
            case 10: 
                int antenna;
                cout << "Select antenna (0 - Omnidirectional, 1 - Yagi, 2 - Dish): ";
                cin >> antenna;
                Boombox.SetAntenna(static_cast<RadioAntenna>(antenna));
                break;
            case 11: 
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
    printf("---------------------------------------------\n");
    printf("--------Object-oriented radio model----------\n");
    printf("---------------------------------------------\n");
    printf("--------Select one of these options----------\n");
    printf("---------------------------------------------\n");
    printf("[0 - Turn off]\n");
    printf("[1 - Turn on]\n");
    printf("[2 - Set frequency]\n");
    printf("[3 - Set output power]\n");
    printf("[4 - Set range]\n");
    printf("[5 - Set sensitivity]\n");
    printf("[6 - Set impedance]\n");
    printf("[7 - Set signal-to-noise ratio]\n");
    printf("[8 - Set number of channels]\n");
    printf("[9 - Set ports]\n");
    printf("[10 - Set antenna]\n");
    printf("[11 - Exit]\n");
    printf("---------------------------------------------\n");
    printf("\n\n\n");
}

// Виведення інформації про стан радіо
void PrintRadioInfo(const Radio& radio)
{
    printf("---------------------------------------------\n");
    printf("---------------State of radio:---------------\n");
    printf("---------------------------------------------\n");
    printf("Power: %d\n", radio.IsPoweredOn());
    printf("State: %s\n", radio.IsPoweredOn() ? "On" : "Off");
    printf("Frequency: %.2f MHz\n", radio.GetFrequency());
    printf("Output power: %.2f W\n", radio.GetOutputPower());
    printf("Range: %s\n", radio.GetRangeAsString().c_str());
    printf("Sensitivity: %.2f dBm\n", radio.GetSensitivity());
    printf("Impedance: %.2f ohm\n", radio.GetImpedance());
    printf("Signal-to-noise ratio: %.2f dB\n", radio.GetSignalToNoiseRatio());
    printf("Number of channels: %d\n", radio.GetNumberOfChannels());
    printf("Ports: %s\n", radio.GetPortsAsString().c_str());
    printf("Antenna: %s\n", radio.GetAntennaAsString().c_str());
    printf("---------------------------------------------\n");
    printf("\n\n");
}