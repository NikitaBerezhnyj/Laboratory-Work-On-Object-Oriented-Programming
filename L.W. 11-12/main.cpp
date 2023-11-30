#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <filesystem>
#include "radio.hpp"

using namespace std;

// Функція для виводу меню користувача
void UserMenu(int user_count);

// Функція для виводу інформації про радіо
void PrintRadioInfo(const FM_Radio& Phillips, const AM_Radio& Transistorola, int radioNum);

// Функція перевірки збережень користувача
void CheckData(FM_Radio& Phillips, AM_Radio& Transistorola);

// Функція створення збережень користувача
void CreateData();

// 
void LoadData(FM_Radio& Phillips, AM_Radio& Transistorola);

// Функція збереження даних користувача
void SaveData(const FM_Radio& Phillips, const AM_Radio& Transistorola, int radioNum);

int main()
{    
    User client;
    Admin admin;
    Manager manager;
    Director director;

    // Створення об'єкта FM радіо
    FM_Radio Phillips;

    // Створення об'єкта AM радіо
    AM_Radio Transistorola;

    CheckData(Phillips, Transistorola);

    int user_count;
    cout << "Select you user type (0 - client, 1 - admin, 2 - manager, 3 - director): ";
    cin >> user_count;

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
        UserMenu(user_count);

        // Виведення інформації про стан радіо
        PrintRadioInfo(Phillips, Transistorola, radioNum);

        // Очікування вибору користувача
        printf("Enter task code: ");
        cin >> key;

        // Обробка вибору користувача
        switch (user_count)
        {
            case 0:
                switch (key)
                    {
                        case 0:
                            if (radioNum == 0)
                            {
                                client.FM_TurnOff(Phillips);
                            }
                            else if (radioNum == 1)
                            {
                                client.AM_TurnOn(Transistorola);
                            }              
                            break;
                        case 1:
                            if (radioNum == 0)
                            {
                                client.FM_TurnOn(Phillips);
                            }
                            else if (radioNum == 1)
                            {
                                client.AM_TurnOn(Transistorola);
                            }
                            break;
                        case 2: 
                            double frequency;
                            cout << "Enter frequency (MHz): ";
                            cin >> frequency;
                            if (radioNum == 0)
                            {
                                client.FM_ChangeFrequency(Phillips, frequency);
                            }
                            else if (radioNum == 1)
                            {
                                client.AM_ChangeFrequency(Transistorola, frequency);
                            }
                            break;
                        case 3: 
                            double volume;
                            cout << "Enter volume (db): ";
                            cin >> volume;
                            if (radioNum == 0)
                            {
                                client.FM_ChangeVolume(Phillips, volume);
                            }
                            else if (radioNum == 1)
                            {
                                client.AM_ChangeVolume(Transistorola, volume);
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
                                client.FM_SaveFrequency(Phillips, value_and_index);
                            }
                            else if (radioNum == 1)
                            {
                                client.AM_SaveFrequency(Transistorola, value_and_index);
                            }
                            break;
                        case 5:
                            cout << "Select radio (0 - Phillips, 1 - Transistorola): ";
                            cin >> radioNum;
                            break;
                        case 6: 
                            cout << "Select you user type (0 - client, 1 - admin, 2 - manager, 3 - director): ";
                            cin >> user_count;
                            break;
                        case 7: 
                            Phillips.~FM_Radio();
                            Phillips.~FM_Radio();
                            Transistorola.~AM_Radio();
                            Transistorola.~AM_Radio();
                            cout << "All objects have been delated\n";
                            is_work = false;
                            break;
                        case 8:
                            is_work = false;
                            break;
                        default: 
                            cout << "Looks like you made a mistake" << endl;
                            break;
                    }
                break;
            case 1:
                switch (key)
                    {
                        case 0:
                            if (radioNum == 0)
                            {
                                client.FM_TurnOff(Phillips);
                            }
                            else if (radioNum == 1)
                            {
                                client.AM_TurnOn(Transistorola);
                            }              
                            break;
                        case 1:
                            if (radioNum == 0)
                            {
                                client.FM_TurnOn(Phillips);
                            }
                            else if (radioNum == 1)
                            {
                                client.AM_TurnOn(Transistorola);
                            }
                            break;
                        case 2:
                            cout << "Select radio (0 - Phillips, 1 - Transistorola): ";
                            cin >> radioNum;
                            break;
                        case 3: 
                            cout << "Select you user type (0 - client, 1 - admin, 2 - manager, 3 - director): ";
                            cin >> user_count;
                            break;
                        case 4: 
                            Phillips.~FM_Radio();
                            Phillips.~FM_Radio();
                            Transistorola.~AM_Radio();
                            Transistorola.~AM_Radio();
                            cout << "All objects have been delated\n";
                            is_work = false;
                            break;
                        case 5:
                            is_work = false;
                            break;
                        default: 
                            cout << "Looks like you made a mistake" << endl;
                            break;
                    }
                    break;
            case 2:
                switch (key)
                {
                    case 0:
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
                            client.FM_SaveFrequency(Phillips, value_and_index);
                        }
                        else if (radioNum == 1)
                        {
                            client.AM_SaveFrequency(Transistorola, value_and_index);
                        }
                        break;
                    case 1:
                        cout << "Select radio (0 - Phillips, 1 - Transistorola): ";
                        cin >> radioNum;
                        break;
                    case 2: 
                        cout << "Select you user type (0 - client, 1 - admin, 2 - manager, 3 - director): ";
                        cin >> user_count;
                        break;
                    case 3: 
                        Phillips.~FM_Radio();
                        Phillips.~FM_Radio();
                        Transistorola.~AM_Radio();
                        Transistorola.~AM_Radio();
                        cout << "All objects have been delated\n";
                        is_work = false;
                        break;
                    case 4:
                        is_work = false;
                        break;
                    default: 
                        cout << "Looks like you made a mistake" << endl;
                        break;
                }
                break;
            case 3:
                switch (key)
                {
                    case 0: 
                        double frequency;
                        cout << "Enter frequency (MHz): ";
                        cin >> frequency;
                        if (radioNum == 0)
                        {
                            client.FM_ChangeFrequency(Phillips, frequency);
                        }
                        else if (radioNum == 1)
                        {
                            client.AM_ChangeFrequency(Transistorola, frequency);
                        }
                        break;
                    case 1: 
                        double volume;
                        cout << "Enter volume (db): ";
                        cin >> volume;
                        if (radioNum == 0)
                        {
                            client.FM_ChangeVolume(Phillips, volume);
                        }
                        else if (radioNum == 1)
                        {
                            client.AM_ChangeVolume(Transistorola, volume);
                        }
                        break;
                    case 2:
                        cout << "Select radio (0 - Phillips, 1 - Transistorola): ";
                        cin >> radioNum;
                        break;
                    case 3: 
                        cout << "Select you user type (0 - client, 1 - admin, 2 - manager, 3 - director): ";
                        cin >> user_count;
                        break;
                    case 4: 
                        Phillips.~FM_Radio();
                        Phillips.~FM_Radio();
                        Transistorola.~AM_Radio();
                        Transistorola.~AM_Radio();
                        cout << "All objects have been delated\n";
                        is_work = false;
                        break;
                    case 5:
                        is_work = false;
                        break;
                    default: 
                        cout << "Looks like you made a mistake" << endl;
                        break;
                }
                break;
            default:
                cout << "Looks like you made a mistake" << endl;
                break;
        }
        SaveData(Phillips, Transistorola, radioNum);
    } while (is_work == true);
    return 0;
}

// Виведення меню користувача
void UserMenu(int user_count)
{
    switch (user_count)
    {
    case 0:
        system("clear");
        printf("-------------------------------------------------------------------\n");
        printf("--------------------Object-oriented radio model--------------------\n");
        printf("-------------------------------------------------------------------\n");
        printf("--------------------Select one of these options--------------------\n");
        printf("-------------------------------------------------------------------\n");
        printf("------------------------------Client-------------------------------\n");
        printf("-------------------------------------------------------------------\n");
        printf("[0 - Turn off]\n");
        printf("[1 - Turn on]\n");
        printf("[2 - Set frequency]\n");
        printf("[3 - Set volume]\n");
        printf("[4 - Save frequency]\n");
        printf("[5 - Change object]\n");
        printf("[6 - Change user type]\n");
        printf("[7 - Delate all objects]\n");
        printf("[8 - Exit]\n");
        printf("-------------------------------------------------------------------\n");
        printf("\n\n\n");
        break;
    case 1:
        system("clear");
        printf("-------------------------------------------------------------------\n");
        printf("--------------------Object-oriented radio model--------------------\n");
        printf("-------------------------------------------------------------------\n");
        printf("--------------------Select one of these options--------------------\n");
        printf("-------------------------------------------------------------------\n");
        printf("------------------------------Admin--------------------------------\n");
        printf("-------------------------------------------------------------------\n");
        printf("[0 - Turn off]\n");
        printf("[1 - Turn on]\n");
        printf("[2 - Change object]\n");
        printf("[3 - Change user type]\n");
        printf("[4 - Delate all objects]\n");
        printf("[5 - Exit]\n");
        printf("-------------------------------------------------------------------\n");
        printf("\n\n\n");
        break;
    case 2:
        system("clear");
        printf("-------------------------------------------------------------------\n");
        printf("--------------------Object-oriented radio model--------------------\n");
        printf("-------------------------------------------------------------------\n");
        printf("--------------------Select one of these options--------------------\n");
        printf("-------------------------------------------------------------------\n");
        printf("-----------------------------Manager-------------------------------\n");
        printf("-------------------------------------------------------------------\n");
        printf("[0 - Save frequency]\n");
        printf("[1 - Change object]\n");
        printf("[2 - Change user type]\n");
        printf("[3 - Delate all objects]\n");
        printf("[4 - Exit]\n");
        printf("-------------------------------------------------------------------\n");
        printf("\n\n\n");
        break;
    case 3:
        system("clear");
        printf("-------------------------------------------------------------------\n");
        printf("--------------------Object-oriented radio model--------------------\n");
        printf("-------------------------------------------------------------------\n");
        printf("--------------------Select one of these options--------------------\n");
        printf("-------------------------------------------------------------------\n");
        printf("----------------------------Director-------------------------------\n");
        printf("-------------------------------------------------------------------\n");
        printf("[0 - Set frequency]\n");
        printf("[1 - Set volume]\n");
        printf("[2 - Change object]\n");
        printf("[3 - Change user type]\n");
        printf("[4 - Delate all objects]\n");
        printf("[5 - Exit]\n");
        printf("-------------------------------------------------------------------\n");
        printf("\n\n\n");
        break;
    default:
        printf("Error user type\n");
        break;
    }
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

void CheckData(FM_Radio& Phillips, AM_Radio& Transistorola)
{
    char wantLoadSaveChar;
    std::string filename = "radio_data.txt";
    bool is_fail_saves = std::filesystem::exists(filename);
    if (is_fail_saves == true)
    {
        printf("Want you load radio state from saves?\n");
        printf("[y - Yes; n - No]\n");
        cin >> wantLoadSaveChar;
        if (wantLoadSaveChar == 'y')
        {
            LoadData(Phillips, Transistorola);
        }
    }
    else
    {
        CreateData();
    }
}

void CreateData()
{
    ofstream RadioData("radio_data.txt");
    RadioData.close();
}

void SaveData(const FM_Radio& Phillips, const AM_Radio& Transistorola, int radioNum)
{
    ofstream RadioData("radio_data.txt");

    if (radioNum == 0)
    {
        RadioData << "RadioType: FM" << endl;
        RadioData << "Power: " << Phillips.IsPoweredOn() << endl;
        RadioData << "Volume: " << Phillips.GetIVolume() << endl;
        RadioData << "Frequency: " << Phillips.GetFrequency() << endl;
        std::array<double, 5> fmFrequencies = Phillips.GetInstalledFrequency();
        RadioData << "Saved frequencies: " << fmFrequencies[0] << ", " << fmFrequencies[1] << ", " << fmFrequencies[2] << ", " << fmFrequencies[3] << ", " << fmFrequencies[4] << endl;
        
        RadioData << "\n\n\n";

        RadioData << "RadioType: AM" << endl;
        RadioData << "Power: " << Transistorola.IsPoweredOn() << endl;
        RadioData << "Volume: " << Transistorola.GetIVolume() << endl;
        RadioData << "Frequency: " << Transistorola.GetFrequency() << endl;
        std::array<double, 5> amFrequencies = Transistorola.GetInstalledFrequency();
        RadioData << "Saved frequencies: " << amFrequencies[0] << ", " << amFrequencies[1] << ", " << amFrequencies[2] << ", " << amFrequencies[3] << ", " << amFrequencies[4] << endl;
    }

    RadioData.close();
}

void LoadData(FM_Radio& Phillips, AM_Radio& Transistorola)
{
    ifstream RadioData("radio_data.txt");
    if (!RadioData)
    {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    string radioType;
    int power_fm;
    int power_am;
    int volume_fm;
    int volume_am;
    double frequency_fm;
    double frequency_am;
    std::array<double, 2> savedFrequencies_fm;
    std::array<double, 2> savedFrequencies_am;

    while (getline(RadioData, line))
    {
        istringstream iss(line);
        string key;
        iss >> key;

        if (key == "RadioType:")
        {
            iss >> radioType;
        }
        else if (key == "Power:")
        {
            if(radioType == "FM")
            {
                iss >> power_fm;
            }
            else
            {
                iss >> power_am;
            }
        }
        else if (key == "Volume:")
        {
            if(radioType == "FM")
            {
                iss >> volume_fm;
            }
            else
            {
                iss >> volume_am;
            }
        }
        else if (key == "Frequency:")
        {
            if(radioType == "FM")
            {
                iss >> frequency_fm;
            }
            else
            {
                iss >> frequency_am;
            }
        }
        else if (key == "Saved" && iss >> key && key == "frequencies:")
        {
            getline(iss, line);

            istringstream freqStream(line);
            string frequencyStr;
            size_t index = 0;

            while (getline(freqStream, frequencyStr, ','))
            {
                double frequencyValue = stod(frequencyStr);
                // Зберігаємо індекс та значення в двовимірний масив
                if (radioType == "FM")
                {
                    savedFrequencies_fm[0] = frequencyValue;
                    savedFrequencies_fm[1] = index;
                    Phillips.SetInstalledFrequency(savedFrequencies_fm);
                    if((index + 1) < 5)
                    {
                        index++;
                    }
                    else
                    {
                        index = 0;
                    }
                }
                else
                {
                    savedFrequencies_am[0] = frequencyValue;
                    savedFrequencies_am[1] = index;
                    Transistorola.SetInstalledFrequency(savedFrequencies_am);
                    if((index + 1) < 5)
                    {
                        index++;
                    }
                    else
                    {
                        index = 0;
                    }
                }
            }
        }
        else if(key.empty())
        {
            continue;
        }

        if (iss.fail())
        {
            cout << "Error reading file." << endl;
            return;
        }
    }
    if (power_fm == 1)
    {
        Phillips.TurnOn();
    }
    else
    {
        Phillips.TurnOff();
    }
    Phillips.SetVolume(volume_fm);
    Phillips.SetFrequency(frequency_fm);


    if (power_am == 1)
    {
        Transistorola.TurnOn();
    }
    else
    {
        Transistorola.TurnOff();
    }
    Transistorola.SetVolume(volume_am);
    Transistorola.SetFrequency(frequency_am);
    RadioData.close();
}