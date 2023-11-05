#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "radio.hpp"

using namespace std;

// Функція для виводу меню користувача
void UserMenu();

// Функція для виводу інформації про радіо
void PrintRadioInfo(const Radio& Boombox, const Radio& Walkman, const Radio& Panasonic, int radioNum);

int main()
{
    // Створення об'єкта радіо та ініціалізація
    // Конструктор за замовчуванням
    Radio Boombox;
    Boombox.Reset();

    // Конструктор ініціалізації
    Radio Walkman(false, 98.5, 50.0, RadioRange::FM_Medium, 90.0, 75.0, 95.0, 50, RadioPort::FM, RadioAntenna::Yagi);

    // Конструктор копіювання
    Radio Panasonic(Walkman);

    // Вибір об'єкта
    int radioNum;
    cout << "Select radio (0 - Boombox, 1 - Walkman, 2 - Panasonic): ";
    cin >> radioNum;

    // Змінні для вибору та керування циклом
    int key;
    bool is_work = true;

    // Головний цикл програми
    do {
        // Виведення меню користувача
        UserMenu();

        // Виведення інформації про стан радіо
        PrintRadioInfo(Boombox, Walkman, Panasonic, radioNum);

        // Очікування вибору користувача
        printf("Enter task code: ");
        cin >> key;

        // Обробка вибору користувача
        switch (key)
        {
            case 0:
                if (radioNum == 0)
                {
                    Boombox.TurnOff();
                }
                else if (radioNum == 1)
                {
                    Walkman.TurnOff();
                }
                else
                {
                    Panasonic.TurnOff();
                }                
                break;
            case 1:
                if (radioNum == 0)
                {
                    Boombox.TurnOn();
                }
                else if (radioNum == 1)
                {
                    Walkman.TurnOn();
                }
                else
                {
                    Panasonic.TurnOn();
                }  
                break;
            case 2: 
                double frequency;
                cout << "Enter frequency (MHz): ";
                cin >> frequency;
                if (radioNum == 0)
                {
                    Boombox.SetFrequency(frequency);
                }
                else if (radioNum == 1)
                {
                    Walkman.SetFrequency(frequency);
                }
                else
                {
                    Panasonic.SetFrequency(frequency);
                }
                break;
            case 3: 
                float outputPower;
                cout << "Enter output power (W): ";
                cin >> outputPower;
                if (radioNum == 0)
                {
                    Boombox.SetOutputPower(outputPower);
                }
                else if (radioNum == 1)
                {
                    Walkman.SetOutputPower(outputPower);
                }
                else
                {
                    Panasonic.SetOutputPower(outputPower);
                }
                break;
            case 4:
                int range;
                cout << "Select range (0 - FM_Short, 1 - FM_Medium, 2 - FM_Long, 3 - AM_Short, 4 - AM_Medium, 5 - AM_Long, 6 - SW, 7 - LW): ";
                cin >> range;
                if (radioNum == 0)
                {
                    Boombox.SetRange(static_cast<RadioRange>(range));
                }
                else if (radioNum == 1)
                {
                    Walkman.SetRange(static_cast<RadioRange>(range));
                }
                else
                {
                    Panasonic.SetRange(static_cast<RadioRange>(range));
                }
                break;
            case 5: 
                float sensitivity;
                cout << "Enter sensitivity (dBm): ";
                cin >> sensitivity;
                if (radioNum == 0)
                {
                    Boombox.SetSensitivity(sensitivity);
                }
                else if (radioNum == 1)
                {
                    Walkman.SetSensitivity(sensitivity);
                }
                else
                {
                    Panasonic.SetSensitivity(sensitivity);
                }
                break;
            case 6: 
                float impedance;
                cout << "Enter impedance (ohm): ";
                cin >> impedance;
                if (radioNum == 0)
                {
                    Boombox.SetImpedance(impedance);
                }
                else if (radioNum == 1)
                {
                    Walkman.SetImpedance(impedance);
                }
                else
                {
                    Panasonic.SetImpedance(impedance);
                }
                break;
            case 7: 
                float snr;
                cout << "Enter signal-to-noise ratio (dB): ";
                cin >> snr;
                if (radioNum == 0)
                {
                    Boombox.SetSignalToNoiseRatio(snr);
                }
                else if (radioNum == 1)
                {
                    Walkman.SetSignalToNoiseRatio(snr);
                }
                else
                {
                    Panasonic.SetSignalToNoiseRatio(snr);
                }
                break;
            case 8: 
                int numChannels;
                cout << "Enter number of channels: ";
                cin >> numChannels;
                if (radioNum == 0)
                {
                    Boombox.SetNumberOfChannels(numChannels);
                }
                else if (radioNum == 1)
                {
                    Walkman.SetNumberOfChannels(numChannels);
                }
                else
                {
                    Panasonic.SetNumberOfChannels(numChannels);
                }
                break;
            case 9: 
                int ports;
                cout << "Select ports (0 - AM, 1 - FM, 2 - SW, 3 - LW): ";
                cin >> ports;
                if (radioNum == 0)
                {
                    Boombox.SetPorts(static_cast<RadioPort>(ports));
                }
                else if (radioNum == 1)
                {
                    Walkman.SetPorts(static_cast<RadioPort>(ports));
                }
                else
                {
                    Panasonic.SetPorts(static_cast<RadioPort>(ports));
                }
                break;
            case 10: 
                int antenna;
                cout << "Select antenna (0 - Omnidirectional, 1 - Yagi, 2 - Dish): ";
                cin >> antenna;
                if (radioNum == 0)
                {
                    Boombox.SetAntenna(static_cast<RadioAntenna>(antenna));
                }
                else if (radioNum == 1)
                {
                    Walkman.SetAntenna(static_cast<RadioAntenna>(antenna));
                }
                else
                {
                    Panasonic.SetAntenna(static_cast<RadioAntenna>(antenna));
                }
                break;
            case 11:
                cout << "Select radio (0 - Boombox, 1 - Walkman, 2 - Panasonic): ";
                cin >> radioNum;
                break;
            case 12: 
                Boombox.~Radio();
                Boombox.~Radio();
                Walkman.~Radio();
                Walkman.~Radio();
                Panasonic.~Radio();
                Panasonic.~Radio();
                cout << "All objects have been delated\n";
                is_work = false;
                break;
            case 13: 
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
    printf("[11 - Change object]\n");
    printf("[12 - Delate all objects]\n");
    printf("[13 - Exit]\n");
    printf("---------------------------------------------\n");
    printf("\n\n\n");
}

// Виведення інформації про стан радіо
void PrintRadioInfo(const Radio& Boombox, const Radio& Walkman, const Radio& Panasonic, int radioNum)
{
    if (radioNum == 0)
    {
        printf("---------------------------------------------\n");
        printf("---------------State of Boombox:-------------\n");
        printf("---------------------------------------------\n");
        printf("Power: %d\n", Boombox.IsPoweredOn());
        printf("State: %s\n", Boombox.IsPoweredOn() ? "On" : "Off");
        printf("Frequency: %.2f MHz\n", Boombox.GetFrequency());
        printf("Output power: %.2f W\n", Boombox.GetOutputPower());
        printf("Range: %s\n", Boombox.GetRangeAsString().c_str());
        printf("Sensitivity: %.2f dBm\n", Boombox.GetSensitivity());
        printf("Impedance: %.2f ohm\n", Boombox.GetImpedance());
        printf("Signal-to-noise ratio: %.2f dB\n", Boombox.GetSignalToNoiseRatio());
        printf("Number of channels: %d\n", Boombox.GetNumberOfChannels());
        printf("Ports: %s\n", Boombox.GetPortsAsString().c_str());
        printf("Antenna: %s\n", Boombox.GetAntennaAsString().c_str());
        printf("---------------------------------------------\n");
        printf("\n\n");
    }
    else if (radioNum == 1)
    {
        printf("---------------------------------------------\n");
        printf("---------------State of Walkman:-------------\n");
        printf("---------------------------------------------\n");
        printf("Power: %d\n", Walkman.IsPoweredOn());
        printf("State: %s\n", Walkman.IsPoweredOn() ? "On" : "Off");
        printf("Frequency: %.2f MHz\n", Walkman.GetFrequency());
        printf("Output power: %.2f W\n", Walkman.GetOutputPower());
        printf("Range: %s\n", Walkman.GetRangeAsString().c_str());
        printf("Sensitivity: %.2f dBm\n", Walkman.GetSensitivity());
        printf("Impedance: %.2f ohm\n", Walkman.GetImpedance());
        printf("Signal-to-noise ratio: %.2f dB\n", Walkman.GetSignalToNoiseRatio());
        printf("Number of channels: %d\n", Walkman.GetNumberOfChannels());
        printf("Ports: %s\n", Walkman.GetPortsAsString().c_str());
        printf("Antenna: %s\n", Walkman.GetAntennaAsString().c_str());
        printf("---------------------------------------------\n");
        printf("\n\n");
    }
    else
    {
        printf("---------------------------------------------\n");
        printf("---------------State of Panasonic:-----------\n");
        printf("---------------------------------------------\n");
        printf("Power: %d\n", Panasonic.IsPoweredOn());
        printf("State: %s\n", Panasonic.IsPoweredOn() ? "On" : "Off");
        printf("Frequency: %.2f MHz\n", Panasonic.GetFrequency());
        printf("Output power: %.2f W\n", Panasonic.GetOutputPower());
        printf("Range: %s\n", Panasonic.GetRangeAsString().c_str());
        printf("Sensitivity: %.2f dBm\n", Panasonic.GetSensitivity());
        printf("Impedance: %.2f ohm\n", Panasonic.GetImpedance());
        printf("Signal-to-noise ratio: %.2f dB\n", Panasonic.GetSignalToNoiseRatio());
        printf("Number of channels: %d\n", Panasonic.GetNumberOfChannels());
        printf("Ports: %s\n", Panasonic.GetPortsAsString().c_str());
        printf("Antenna: %s\n", Panasonic.GetAntennaAsString().c_str());
        printf("---------------------------------------------\n");
        printf("\n\n");
    }
}