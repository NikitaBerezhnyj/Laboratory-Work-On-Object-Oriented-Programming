#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <limits>
#include <filesystem>
#include <stdexcept>
#include <exception>
#include "radio.hpp"

using namespace std;
using std::exception;

// Стандартні функції програми
// Функція для виводу меню користувача
void UserMenu(int user_count);
// Функція для виводу інформації про радіо
void PrintRadioInfo(const FM_Radio& Phillips, const AM_Radio& Sony, int radioNum);
// Функція перевірки збережень користувача
void CheckData(FM_Radio& Phillips, AM_Radio& Sony);
// Функція створення збережень користувача
void CreateData();
// Завантаження даних користувача із файлу
void LoadData(FM_Radio& Phillips, AM_Radio& Sony);
// Функція збереження даних користувача
void SaveData(const FM_Radio& Phillips, const AM_Radio& Sony, int radioNum);

// Клас виключень
class UserInputException : public std::exception
{
	public:
    	explicit UserInputException(const char* message) : msg(message) {}
    	const char* what() const noexcept override
    	{
        	return msg.c_str();
    	}
    	void waitForEnter() const
    	{
        	cout << "Press Enter to continue... ";
        	cin.get();
    	}
	private:
    	std::string msg;
};

int main()
{
	// Створення користувачів
	User client;
	Admin admin;
	Manager manager;
	Director director;

	// Створення об'єктів радіо
	FM_Radio Phillips;
	AM_Radio Sony;

	CheckData(Phillips, Sony);

	int user_count;
	int radioNum;
	bool is_choose = false;

	// Запис значень в коректному діапазоні
	while (is_choose == false)
	{
    	// Вибір типу користувача
    	cout << "Select your user type (0 - client, 1 - admin, 2 - manager, 3 - director): ";
    	while (!(cin >> user_count) || user_count < 0 || user_count > 3)
    	{
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	cout << "Error in user type. Please enter a valid value (0 - 3): ";
    	}

    	// Вибір об'єкта
    	cout << "Select radio (0 - Phillips, 1 - Sony): ";
    	while (!(cin >> radioNum) || (radioNum != 0 && radioNum != 1))
    	{
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	cout << "Error in radio type. Please enter a valid value (0 or 1): ";
    	}

    	is_choose = true;
	}
    
	// Змінні для вибору та керування циклом
	int key;
	bool is_work = true;

	// Головний цикл програми
	do {
    	// Виведення меню користувача
    	UserMenu(user_count);

    	// Виведення інформації про стан радіо
    	PrintRadioInfo(Phillips, Sony, radioNum);

    	// Очікування вибору користувача
    	try
    	{
        	printf("Enter task code: ");
        	cin >> key;
        	if (cin.fail())
        	{
            	cin.clear();
            	cin.ignore(numeric_limits<streamsize>::max(), '\n');
            	throw UserInputException("Invalid input. This object has no tasks with such code.");
        	}
    	}
    	catch (const UserInputException& e)
    	{
        	cerr << "Error: " << e.what() << endl;
        	e.waitForEnter();
        	continue;
    	}

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
                            	client.AM_TurnOn(Sony);
                        	}         	 
                        	break;
                    	case 1:
                        	if (radioNum == 0)
                        	{
                            	client.FM_TurnOn(Phillips);
                        	}
                        	else if (radioNum == 1)
                        	{
                            	client.AM_TurnOn(Sony);
                        	}
                        	break;
                    	case 2:
                        	try {
                            	double frequency;
                            	cout << "Enter frequency (MHz): ";
                            	cin >> frequency;
                            	if (cin.fail())
                            	{
                                	cin.clear();
                                	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                	throw UserInputException("Invalid input. Please enter a valid frequency.");
                            	}
                            	if (radioNum == 0)
                            	{
                                	client.FM_ChangeFrequency(Phillips, frequency);
                            	}
                            	else if (radioNum == 1)
                            	{
                                	client.AM_ChangeFrequency(Sony, frequency);
                            	}
                        	}
                        	catch (const UserInputException& e)
                        	{
                            	cerr << "Error: " << e.what() << endl;
                            	e.waitForEnter();
                            	continue;
                        	}
                        	break;
                    	case 3:
                        	try
                        	{
                            	int volume;
                            	cout << "Enter volume (db): ";
                            	cin >> volume;
                            	if (cin.fail())
                            	{
                                	cin.clear();
                                	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                	throw UserInputException("Invalid input. Please enter a valid volume.");
                            	}
                            	if (radioNum == 0)
                            	{
                                	client.FM_ChangeVolume(Phillips, volume);
                            	}
                            	else if (radioNum == 1)
                            	{
                                	client.AM_ChangeVolume(Sony, volume);
                            	}
                        	}
                        	catch(const UserInputException& e)
                        	{
                            	cerr << "Error: " << e.what() << endl;
                            	e.waitForEnter();
                            	continue;
                        	}
                        	break;
                    	case 4:
                        	try
                        	{
                            	int index;
                            	double value;
                            	cout << "Enter index for saving this frequency: ";
                            	cin >> index;
                            	if (cin.fail())
                            	{
                                	cin.clear();
                                	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                	throw UserInputException("Invalid input. Please enter a valid index frequency.");
                            	}
                            	cout << "Enter frequency for saving: ";
                            	cin >> value;
                            	if (cin.fail())
                            	{
                                	cin.clear();
                                	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                	throw UserInputException("Invalid input. Please enter a valid frequency.");
                            	}
                            	std::array<double, 2> value_and_index;
                            	value_and_index[0] = value;
                            	value_and_index[1] = index;
                            	if (radioNum == 0)
                            	{
                                	client.FM_SaveFrequency(Phillips, value_and_index);
                            	}
                            	else if (radioNum == 1)
                            	{
                                	client.AM_SaveFrequency(Sony, value_and_index);
                            	}
                        	}
                        	catch(const UserInputException& e)
                        	{
                            	cerr << "Error: " << e.what() << endl;
                            	e.waitForEnter();
                            	continue;
                        	}
                        	break;
                    	case 5:
                        	try
                        	{
                            	cout << "Select radio (0 - Phillips, 1 - Sony): ";
                            	cin >> radioNum;
                            	if (cin.fail())
                            	{
                                	cin.clear();
                                	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                	throw UserInputException("Invalid input. Please enter a valid code for radio.");
                            	}
                        	}
                        	catch(const UserInputException& e)
                        	{
                            	cerr << "Error: " << e.what() << endl;
                            	e.waitForEnter();
                            	continue;
                        	}
                        	break;
                    	case 6:
                        	try
                        	{
                            	cout << "Select you user type (0 - client, 1 - admin, 2 - manager, 3 - director): ";
                            	cin >> user_count;
                            	if (cin.fail())
                            	{
                                	cin.clear();
                                	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                	throw UserInputException("Invalid input. Please enter a valid user type.");
                            	}
                        	}
                        	catch(const UserInputException& e)
                        	{
                            	cerr << "Error: " << e.what() << endl;
                            	e.waitForEnter();
                            	continue;
                        	}
                        	break;
                    	case 7:
                        	Phillips.~FM_Radio();
                        	Phillips.~FM_Radio();
                        	Sony.~AM_Radio();
                        	Sony.~AM_Radio();
                        	cout << "All objects have been delated\n";
                        	is_work = false;
                        	break;
                    	case 8:
                        	is_work = false;
                        	break;
                    	default:
                        	cout << "Looks like you made a mistake" << endl;
                        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        	cout << "Press Enter to continue... ";
                        	cin.get();
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
                            	client.AM_TurnOn(Sony);
                        	}         	 
                        	break;
                    	case 1:
                        	if (radioNum == 0)
                        	{
                            	client.FM_TurnOn(Phillips);
                        	}
                        	else if (radioNum == 1)
                        	{
                            	client.AM_TurnOn(Sony);
                        	}
                        	break;
                    	case 2:
                        	try
                        	{
                            	cout << "Select radio (0 - Phillips, 1 - Sony): ";
                            	cin >> radioNum;
                            	if (cin.fail())
                            	{
                                	cin.clear();
                                	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                	throw UserInputException("Invalid input. Please enter a valid code for radio.");
                            	}
                        	}
                        	catch(const UserInputException& e)
                        	{
                            	cerr << "Error: " << e.what() << endl;
                            	e.waitForEnter();
                            	continue;
                        	}
                        	break;
                    	case 3:
                        	try
                        	{
                            	cout << "Select you user type (0 - client, 1 - admin, 2 - manager, 3 - director): ";
                            	cin >> user_count;
                            	if (cin.fail())
                            	{
                                	cin.clear();
                                	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                	throw UserInputException("Invalid input. Please enter a valid user type.");
                            	}
                        	}
                        	catch(const UserInputException& e)
                        	{
                            	cerr << "Error: " << e.what() << endl;
                            	e.waitForEnter();
                            	continue;
                        	}
                        	break;
                    	case 4:
                        	Phillips.~FM_Radio();
                        	Phillips.~FM_Radio();
                        	Sony.~AM_Radio();
                        	Sony.~AM_Radio();
                        	cout << "All objects have been delated\n";
                        	is_work = false;
                        	break;
                    	case 5:
                        	is_work = false;
                        	break;
                    	default:
                        	cout << "Looks like you made a mistake" << endl;
                        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        	cout << "Press Enter to continue... ";
                        	cin.get();
                        	break;
                	}
                	break;
        	case 2:
            	switch (key)
            	{
                	case 0:
                    	try
                    	{
                        	int index;
                        	double value;
                        	cout << "Enter index for saving this frequency: ";
                        	cin >> index;
                        	if (cin.fail())
                        	{
                            	cin.clear();
                            	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            	throw UserInputException("Invalid input. Please enter a valid index frequency.");
                        	}
                        	cout << "Enter frequency for saving: ";
                        	cin >> value;
                        	if (cin.fail())
                        	{
                            	cin.clear();
                            	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            	throw UserInputException("Invalid input. Please enter a valid frequency.");
                        	}
                        	std::array<double, 2> value_and_index;
                        	value_and_index[0] = value;
                        	value_and_index[1] = index;
                        	if (radioNum == 0)
                        	{
                            	client.FM_SaveFrequency(Phillips, value_and_index);
                        	}
                        	else if (radioNum == 1)
                        	{
                            	client.AM_SaveFrequency(Sony, value_and_index);
                        	}
                    	}
                    	catch(const UserInputException& e)
                    	{
                        	cerr << "Error: " << e.what() << endl;
                        	e.waitForEnter();
                        	continue;
                    	}
                    	break;
                	case 1:
                    	try
                    	{
                        	cout << "Select radio (0 - Phillips, 1 - Sony): ";
                        	cin >> radioNum;
                        	if (cin.fail())
                        	{
                            	cin.clear();
                            	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            	throw UserInputException("Invalid input. Please enter a valid code for radio.");
                        	}
                    	}
                    	catch(const UserInputException& e)
                    	{
                        	cerr << "Error: " << e.what() << endl;
                        	e.waitForEnter();
                        	continue;
                    	}
                    	break;
                	case 2:
                    	try
                    	{
                        	cout << "Select you user type (0 - client, 1 - admin, 2 - manager, 3 - director): ";
                        	cin >> user_count;
                        	if (cin.fail())
                        	{
                            	cin.clear();
                            	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            	throw UserInputException("Invalid input. Please enter a valid user type.");
                        	}
                    	}
                    	catch(const UserInputException& e)
                    	{
                        	cerr << "Error: " << e.what() << endl;
                        	e.waitForEnter();
                        	continue;
                    	}
                    	break;
                	case 3:
                    	Phillips.~FM_Radio();
                    	Phillips.~FM_Radio();
                    	Sony.~AM_Radio();
                    	Sony.~AM_Radio();
                    	cout << "All objects have been delated\n";
                    	is_work = false;
                    	break;
                	case 4:
                    	is_work = false;
                    	break;
                	default:
                    	cout << "Looks like you made a mistake" << endl;
                    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    	cout << "Press Enter to continue... ";
                    	cin.get();
                    	break;
            	}
            	break;
        	case 3:
            	switch (key)
            	{
                	case 0:
                    	try {
                        	double frequency;
                        	cout << "Enter frequency (MHz): ";
                        	cin >> frequency;
                        	if (cin.fail())
                        	{
                            	cin.clear();
                            	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            	throw UserInputException("Invalid input. Please enter a valid frequency.");
                        	}
                        	if (radioNum == 0)
                        	{
                            	client.FM_ChangeFrequency(Phillips, frequency);
                        	}
                        	else if (radioNum == 1)
                        	{
                            	client.AM_ChangeFrequency(Sony, frequency);
                        	}
                    	}
                    	catch (const UserInputException& e)
                    	{
                        	cerr << "Error: " << e.what() << endl;
                        	e.waitForEnter();
                        	continue;
                    	}
                    	break;
                	case 1:
                    	try
                    	{
                        	int volume;
                        	cout << "Enter volume (db): ";
                        	cin >> volume;
                        	if (cin.fail())
                        	{
                            	cin.clear();
                            	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            	throw UserInputException("Invalid input. Please enter a valid volume.");
                        	}
                        	if (radioNum == 0)
                        	{
                            	client.FM_ChangeVolume(Phillips, volume);
                        	}
                        	else if (radioNum == 1)
                        	{
                            	client.AM_ChangeVolume(Sony, volume);
                        	}
                    	}
                    	catch(const UserInputException& e)
                    	{
                        	cerr << "Error: " << e.what() << endl;
                        	e.waitForEnter();
                        	continue;
                    	}
                    	break;
                	case 2:
                    	try
                    	{
                        	cout << "Select radio (0 - Phillips, 1 - Sony): ";
                        	cin >> radioNum;
                        	if (cin.fail())
                        	{
                            	cin.clear();
                            	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            	throw UserInputException("Invalid input. Please enter a valid code for radio.");
                        	}
                    	}
                    	catch(const UserInputException& e)
                    	{
                        	cerr << "Error: " << e.what() << endl;
                        	e.waitForEnter();
                        	continue;
                    	}
                    	break;
                	case 3:
                    	try
                    	{
                        	cout << "Select you user type (0 - client, 1 - admin, 2 - manager, 3 - director): ";
                        	cin >> user_count;
                        	if (cin.fail())
                        	{
                            	cin.clear();
                            	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            	throw UserInputException("Invalid input. Please enter a valid user type.");
                        	}
                    	}
                    	catch(const UserInputException& e)
                    	{
                        	cerr << "Error: " << e.what() << endl;
                        	e.waitForEnter();
                        	continue;
                    	}
                    	break;
                	case 4:
                    	Phillips.~FM_Radio();
                    	Phillips.~FM_Radio();
                    	Sony.~AM_Radio();
                    	Sony.~AM_Radio();
                    	cout << "All objects have been delated\n";
                    	is_work = false;
                    	break;
                	case 5:
                    	is_work = false;
                    	break;
                	default:
                    	cout << "Looks like you made a mistake" << endl;
                    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    	cout << "Press Enter to continue... ";
                    	cin.get();
                    	break;
            	}
            	break;
        	default:
            	cout << "Looks like you made a mistake" << endl;
            	cin.ignore(numeric_limits<streamsize>::max(), '\n');
            	cout << "Press Enter to continue... ";
            	cin.get();
            	break;
    	}
    	SaveData(Phillips, Sony, radioNum);
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
void PrintRadioInfo(const FM_Radio& Phillips, const AM_Radio& Sony, int radioNum)
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
    	printf("--------------------------State of Sony:---------------------------\n");
    	printf("-------------------------------------------------------------------\n");
    	printf("Power: %d\n", Sony.IsPoweredOn());
    	printf("State: %s\n", Sony.IsPoweredOn() ? "On" : "Off");
    	printf("Volume: %.i Db\n", Sony.GetIVolume());
    	printf("Frequency: %.2f MHz\n", Sony.GetFrequency());
    	std::array<double, 5> frequencies = Sony.GetInstalledFrequency();
    	printf("Saved frequencies: %.2f MHz, %.2f MHz, %.2f MHz, %.2f MHz, %.2f MHz\n", frequencies[0], frequencies[1], frequencies[2], frequencies[3], frequencies[4]);
    	printf("-------------------------------------------------------------------\n");
    	printf("\n\n");
	}
}

// Перевірка збережень користувача
void CheckData(FM_Radio& Phillips, AM_Radio& Sony)
{
	char wantLoadSaveChar;
	std::string filename = "radio_data.bin";
	bool is_fail_saves = std::filesystem::exists(filename);
	if (is_fail_saves)
	{
    	cout << "Want you load radio state from saves?" << endl;
    	cout << "[y - Yes; n - No] ";
    	while (true)
    	{
        	cin >> wantLoadSaveChar;

        	if (wantLoadSaveChar == 'y' || wantLoadSaveChar == 'n')
        	{
            	break;
        	}
        	else
        	{
            	cout << "Error. Please enter correct character [y - Yes; n - No] ";
            	cin.clear();
            	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        	}
    	}
    	if (wantLoadSaveChar == 'y')
    	{
        	LoadData(Phillips, Sony);
    	}
	}
	else
	{
    	CreateData();
	}
}

// Створення збережень користувача
void CreateData()
{
	ofstream RadioData("radio_data.bin");
	RadioData.close();
}

// Завантаження даних користувача із файлу
void SaveData(const FM_Radio& Phillips, const AM_Radio& Sony, int radioNum)
{
	ofstream RadioData("radio_data.bin", ios::binary);
	if (radioNum == 0)
	{
    	// Зберігаємо дані об'єкта FM_Radio
    	RadioData.write(reinterpret_cast<const char*>(&Phillips), sizeof(FM_Radio));
    	// Зберігаємо дані об'єкта AM_Radio
    	RadioData.write(reinterpret_cast<const char*>(&Sony), sizeof(AM_Radio));
	}
	RadioData.close();
}

// Збереження даних користувача
void LoadData(FM_Radio& Phillips, AM_Radio& Sony)
{
	ifstream RadioData("radio_data.bin", ios::binary);
	if (!RadioData)
	{
    	cout << "Error opening file." << endl;
    	return;
	}
	// Завантажуємо дані об'єкта FM_Radio
	RadioData.read(reinterpret_cast<char*>(&Phillips), sizeof(FM_Radio));
	// Завантажуємо дані об'єкта AM_Radio
	RadioData.read(reinterpret_cast<char*>(&Sony), sizeof(AM_Radio));
	RadioData.close();
}