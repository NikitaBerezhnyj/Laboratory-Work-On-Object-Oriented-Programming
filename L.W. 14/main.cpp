#include "utility.hpp"
#include "radio.hpp"
#include "users.hpp"
#include "data.hpp"
#include "error.hpp"

// Стандартні функції програми
// Функція для виводу меню користувача
void UserMenu(int user_count);
// Функція для виводу інформації про радіо
void PrintRadioInfo(const FM_Radio &Phillips, const AM_Radio &Sony, int radioNum);
// Функція перевірки збережень користувача
void CheckData(FM_Radio &Phillips, AM_Radio &Sony);

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
	while (!is_choose)
	{
		// Вибір об'єкта
		radioNum = -1;
		while (radioNum != 0 && radioNum != 1)
		{
			radioNum = GetNumber("Select radio (0 - Phillips, 1 - Sony): ");
			if (radioNum != 0 && radioNum != 1)
			{
				WarningMessage("Error in radio type. Please enter a valid value (0 or 1): ");
			}
		}

		// Вибір типу користувача
		user_count = -1;
		while (user_count < 0 || user_count > 3)
		{
			user_count = GetNumber("Select your user type (0 - client, 1 - admin, 2 - manager, 3 - director): ");
			if (user_count < 0 || user_count > 3)
			{
				WarningMessage("Error in user type. Please enter a valid value (0 - 3): ");
			}
		}

		is_choose = true;
	}

	// Змінні для вибору та керування циклом
	int key;
	bool is_work = true;

	// Головний цикл програми
	do
	{
		// Виведення меню користувача
		UserMenu(user_count);

		// Виведення інформації про стан радіо
		PrintRadioInfo(Phillips, Sony, radioNum);

		// Очікування вибору користувача
		try
		{
			key = GetNumber("Enter task code: ");
			if (key == -1)
			{
				throw UserInputException("Invalid input. Please enter a valid task number.");
				continue;
			}
		}
		catch (const UserInputException &e)
		{
			WarningMessage("Error: " + string(e.what()));
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
					client.AM_TurnOff(Sony);
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
					double frequency = GetDouble("Enter frequency (MHz): ");
					if (frequency == -1)
					{
						throw UserInputException("Invalid input. Please enter a valid frequency.");
					}
					else
					{
						if (radioNum == 0)
						{
							client.FM_ChangeFrequency(Phillips, frequency);
						}
						else if (radioNum == 1)
						{
							client.AM_ChangeFrequency(Sony, frequency);
						}
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 3:
				try
				{
					int volume = GetNumber("Enter volume (db): ");
					if (volume == -1)
					{
						throw UserInputException("Invalid input. Please enter a valid volume.");
					}
					else
					{
						if (radioNum == 0)
						{
							client.FM_ChangeVolume(Phillips, volume);
						}
						else if (radioNum == 1)
						{
							client.AM_ChangeVolume(Sony, volume);
						}
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 4:
				try
				{
					double value = GetDouble("Enter frequency for saving: ");
					if (value == -1)
					{
						throw UserInputException("Invalid input. Please enter a valid frequency.");
					}
					else
					{
						int index = GetNumber("Enter index for saving this frequency [1 - 5]: ");
						if (index == -1 || index < 1 || index > 5)
						{
							throw UserInputException("Invalid input. Please enter a valid index frequency.");
						}
						else
						{
							std::array<double, 2> value_and_index;
							value_and_index[0] = value;
							value_and_index[1] = index - 1;
							if (radioNum == 0)
							{
								client.FM_SaveFrequency(Phillips, value_and_index);
							}
							else if (radioNum == 1)
							{
								client.AM_SaveFrequency(Sony, value_and_index);
							}
						}
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 5:
				try
				{
					int index = GetNumber("Enter index for load frequency from save [1 - 5]: ");
					if (index == -1)
					{
						throw UserInputException("Invalid input. Please enter a valid frequency.");
					}
					else
					{
						if (radioNum == 0)
						{
							client.FM_LoadFrequency(Phillips, index);
						}
						else if (radioNum == 1)
						{
							client.AM_LoadFrequency(Sony, index);
						}
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 6:
				try
				{
					int changed_radio = GetNumber("Select radio (0 - Phillips, 1 - Sony): ");
					if (changed_radio == 0 || changed_radio == 1)
					{
						radioNum = changed_radio;
					}
					else
					{
						throw UserInputException("Invalid input. Please enter a valid code for radio.");
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 7:
				try
				{
					int changed_user = GetNumber("Select you user type (0 - client, 1 - admin, 2 - manager, 3 - director): ");
					if (changed_user >= 0 && changed_user <= 3)
					{
						user_count = changed_user;
					}
					else
					{
						throw UserInputException("Invalid input. Please enter a valid user type.");
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 8:
				try
				{
					char wantDeleteObjectChar;
					while (true)
					{
						wantDeleteObjectChar = GetChar("Are you sure you want to delete objects? [y - Yes; n - No] ");
						if (wantDeleteObjectChar == ' ')
						{
							throw UserInputException("Please enter correct character");
						}
						else
						{
							break;
						}
					}
					if (wantDeleteObjectChar == 'y')
					{
						Phillips.~FM_Radio();
						Phillips.~FM_Radio();
						Sony.~AM_Radio();
						Sony.~AM_Radio();
						SuccessMessage("All objects have been deleted");
						is_work = false;
					}
					break;
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 9:
				try
				{
					char wantExitChar;
					while (true)
					{
						wantExitChar = GetChar("Are you sure you want to exit? [y - Yes; n - No] ");
						if (wantExitChar == ' ')
						{
							throw UserInputException("Please enter correct character");
						}
						else
						{
							break;
						}
					}
					if (wantExitChar == 'y')
					{
						SuccessMessage("Thanks for work");
						is_work = false;
					}
					break;
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			default:
				WarningMessage("Looks like you made a mistake");
				std::cout << "Press Enter to continue... ";
				std::string tmp_str;
				std::getline(std::cin, tmp_str);
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
					int changed_radio = GetNumber("Select radio (0 - Phillips, 1 - Sony): ");
					if (changed_radio == 0 || changed_radio == 1)
					{
						radioNum = changed_radio;
					}
					else
					{
						throw UserInputException("Invalid input. Please enter a valid code for radio.");
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 3:
				try
				{
					int changed_user = GetNumber("Select you user type (0 - client, 1 - admin, 2 - manager, 3 - director): ");
					if (changed_user >= 0 && changed_user <= 3)
					{
						user_count = changed_user;
					}
					else
					{
						throw UserInputException("Invalid input. Please enter a valid user type.");
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 4:
				try
				{
					char wantDeleteObjectChar;
					while (true)
					{
						wantDeleteObjectChar = GetChar("Are you sure you want to delete objects? [y - Yes; n - No] ");
						if (wantDeleteObjectChar == ' ')
						{
							throw UserInputException("Please enter correct character");
						}
						else
						{
							break;
						}
					}
					if (wantDeleteObjectChar == 'y')
					{
						Phillips.~FM_Radio();
						Phillips.~FM_Radio();
						Sony.~AM_Radio();
						Sony.~AM_Radio();
						SuccessMessage("All objects have been deleted");
						is_work = false;
					}
					break;
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 5:
				try
				{
					char wantExitChar;
					while (true)
					{
						wantExitChar = GetChar("Are you sure you want to exit? [y - Yes; n - No] ");
						if (wantExitChar == ' ')
						{
							throw UserInputException("Please enter correct character");
						}
						else
						{
							break;
						}
					}
					if (wantExitChar == 'y')
					{
						SuccessMessage("Thanks for work");
						is_work = false;
					}
					break;
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			default:
				WarningMessage("Looks like you made a mistake");
				std::cout << "Press Enter to continue... ";
				std::string tmp_str;
				std::getline(std::cin, tmp_str);
				break;
			}
			break;
		case 2:
			switch (key)
			{
			case 0:
				try
				{
					double value = GetDouble("Enter frequency for saving: ");
					if (value == -1)
					{
						throw UserInputException("Invalid input. Please enter a valid frequency.");
					}
					else
					{
						int index = GetNumber("Enter index for saving this frequency [1 - 5]: ");
						if (index == -1 || index < 1 || index > 5)
						{
							throw UserInputException("Invalid input. Please enter a valid index frequency.");
						}
						else
						{
							std::array<double, 2> value_and_index;
							value_and_index[0] = value;
							value_and_index[1] = index - 1;
							if (radioNum == 0)
							{
								client.FM_SaveFrequency(Phillips, value_and_index);
							}
							else if (radioNum == 1)
							{
								client.AM_SaveFrequency(Sony, value_and_index);
							}
						}
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 1:
				try
				{
					int index = GetNumber("Enter index for load frequency from save [1 - 5]: ");
					if (index == -1)
					{
						throw UserInputException("Invalid input. Please enter a valid frequency.");
					}
					else
					{
						if (radioNum == 0)
						{
							std::array<double, 5> frequencies = Phillips.GetInstalledFrequency();
							double value = frequencies[index - 1];
							if (value == 0)
							{
								throw UserInputException("Index value is empty.");
							}
							client.FM_ChangeFrequency(Phillips, value);
						}
						else if (radioNum == 1)
						{
							std::array<double, 5> frequencies = Sony.GetInstalledFrequency();
							double value = frequencies[index - 1];
							if (value == 0)
							{
								throw UserInputException("Index value is empty.");
							}
							client.AM_ChangeFrequency(Sony, value);
						}
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 2:
				try
				{
					int changed_radio = GetNumber("Select radio (0 - Phillips, 1 - Sony): ");
					if (changed_radio == 0 || changed_radio == 1)
					{
						radioNum = changed_radio;
					}
					else
					{
						throw UserInputException("Invalid input. Please enter a valid code for radio.");
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 3:
				try
				{
					int changed_user = GetNumber("Select you user type (0 - client, 1 - admin, 2 - manager, 3 - director): ");
					if (changed_user >= 0 && changed_user <= 3)
					{
						user_count = changed_user;
					}
					else
					{
						throw UserInputException("Invalid input. Please enter a valid user type.");
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 4:
				try
				{
					char wantDeleteObjectChar;
					while (true)
					{
						wantDeleteObjectChar = GetChar("Are you sure you want to delete objects? [y - Yes; n - No] ");
						if (wantDeleteObjectChar == ' ')
						{
							throw UserInputException("Please enter correct character");
						}
						else
						{
							break;
						}
					}
					if (wantDeleteObjectChar == 'y')
					{
						Phillips.~FM_Radio();
						Phillips.~FM_Radio();
						Sony.~AM_Radio();
						Sony.~AM_Radio();
						SuccessMessage("All objects have been deleted");
						is_work = false;
					}
					break;
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 5:
				try
				{
					char wantExitChar;
					while (true)
					{
						wantExitChar = GetChar("Are you sure you want to exit? [y - Yes; n - No] ");
						if (wantExitChar == ' ')
						{
							throw UserInputException("Please enter correct character");
						}
						else
						{
							break;
						}
					}
					if (wantExitChar == 'y')
					{
						SuccessMessage("Thanks for work");
						is_work = false;
					}
					break;
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			default:
				WarningMessage("Looks like you made a mistake");
				std::cout << "Press Enter to continue... ";
				std::string tmp_str;
				std::getline(std::cin, tmp_str);
				break;
			}
			break;
		case 3:
			switch (key)
			{
			case 0:
				try
				{
					double frequency = GetDouble("Enter frequency (MHz): ");
					if (frequency == -1)
					{
						throw UserInputException("Invalid input. Please enter a valid frequency.");
					}
					else
					{
						if (radioNum == 0)
						{
							client.FM_ChangeFrequency(Phillips, frequency);
						}
						else if (radioNum == 1)
						{
							client.AM_ChangeFrequency(Sony, frequency);
						}
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 1:
				try
				{
					int volume = GetNumber("Enter volume (db): ");
					if (volume == -1)
					{
						throw UserInputException("Invalid input. Please enter a valid volume.");
					}
					else
					{
						if (radioNum == 0)
						{
							client.FM_ChangeVolume(Phillips, volume);
						}
						else if (radioNum == 1)
						{
							client.AM_ChangeVolume(Sony, volume);
						}
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
				break;
			case 2:
				try
				{
					int changed_radio = GetNumber("Select radio (0 - Phillips, 1 - Sony): ");
					if (changed_radio == 0 || changed_radio == 1)
					{
						radioNum = changed_radio;
					}
					else
					{
						throw UserInputException("Invalid input. Please enter a valid code for radio.");
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 3:
				try
				{
					int changed_user = GetNumber("Select you user type (0 - client, 1 - admin, 2 - manager, 3 - director): ");
					if (changed_user >= 0 && changed_user <= 3)
					{
						user_count = changed_user;
					}
					else
					{
						throw UserInputException("Invalid input. Please enter a valid user type.");
					}
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 4:
				try
				{
					char wantDeleteObjectChar;
					while (true)
					{
						wantDeleteObjectChar = GetChar("Are you sure you want to delete objects? [y - Yes; n - No] ");
						if (wantDeleteObjectChar == ' ')
						{
							throw UserInputException("Please enter correct character");
						}
						else
						{
							break;
						}
					}
					if (wantDeleteObjectChar == 'y')
					{
						Phillips.~FM_Radio();
						Phillips.~FM_Radio();
						Sony.~AM_Radio();
						Sony.~AM_Radio();
						SuccessMessage("All objects have been deleted");
						is_work = false;
					}
					break;
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			case 5:
				try
				{
					char wantExitChar;
					while (true)
					{
						wantExitChar = GetChar("Are you sure you want to exit? [y - Yes; n - No] ");
						if (wantExitChar == ' ')
						{
							throw UserInputException("Please enter correct character");
						}
						else
						{
							break;
						}
					}
					if (wantExitChar == 'y')
					{
						SuccessMessage("Thanks for work");
						is_work = false;
					}
					break;
				}
				catch (const UserInputException &e)
				{
					PanicMessage("Error: " + string(e.what()));
					e.waitForEnter();
					continue;
				}
				break;
			default:
				WarningMessage("Looks like you made a mistake");
				std::cout << "Press Enter to continue... ";
				std::string tmp_str;
				std::getline(std::cin, tmp_str);
				break;
			}
			break;
		default:
			WarningMessage("Looks like you made a mistake");
			std::cout << "Press Enter to continue... ";
			std::string tmp_str;
			std::getline(std::cin, tmp_str);
			break;
		}
		DataManager::SaveData(Phillips, Sony, radioNum);
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
		printf("-----------------------------------------------------------------------------\n");
		printf("-------------------------Object-oriented radio model-------------------------\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("-------------------------Select one of these options-------------------------\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("-----------------------------------Client------------------------------------\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("[0 - Turn off]\n");
		printf("[1 - Turn on]\n");
		printf("[2 - Set frequency]\n");
		printf("[3 - Set volume]\n");
		printf("[4 - Save frequency]\n");
		printf("[5 - Load frequency]\n");
		printf("[6 - Change object]\n");
		printf("[7 - Change user type]\n");
		printf("[8 - Delate all objects]\n");
		printf("[9 - Exit]\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("\n\n\n");
		break;
	case 1:
		system("clear");
		printf("-----------------------------------------------------------------------------\n");
		printf("-------------------------Object-oriented radio model-------------------------\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("-------------------------Select one of these options-------------------------\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("-----------------------------------Admin-------------------------------------\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("[0 - Turn off]\n");
		printf("[1 - Turn on]\n");
		printf("[2 - Change object]\n");
		printf("[3 - Change user type]\n");
		printf("[4 - Delate all objects]\n");
		printf("[5 - Exit]\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("\n\n\n");
		break;
	case 2:
		system("clear");
		printf("-----------------------------------------------------------------------------\n");
		printf("-------------------------Object-oriented radio model-------------------------\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("-------------------------Select one of these options-------------------------\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("----------------------------------Manager------------------------------------\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("[0 - Save frequency]\n");
		printf("[1 - Load frequency]\n");
		printf("[2 - Change object]\n");
		printf("[3 - Change user type]\n");
		printf("[4 - Delate all objects]\n");
		printf("[5 - Exit]\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("\n\n\n");
		break;
	case 3:
		system("clear");
		printf("-----------------------------------------------------------------------------\n");
		printf("-------------------------Object-oriented radio model-------------------------\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("-------------------------Select one of these options-------------------------\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("--------------------------------Director-------------------------------------\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("[0 - Set frequency]\n");
		printf("[1 - Set volume]\n");
		printf("[2 - Change object]\n");
		printf("[3 - Change user type]\n");
		printf("[4 - Delate all objects]\n");
		printf("[5 - Exit]\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("\n\n\n");
		break;
	default:
		printf("Error user type\n");
		break;
	}
}

// Виведення інформації про стан радіо
void PrintRadioInfo(const FM_Radio &Phillips, const AM_Radio &Sony, int radioNum)
{
	if (radioNum == 0)
	{
		printf("-----------------------------------------------------------------------------\n");
		printf("------------------------------State of Phillips:-----------------------------\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("Power: %d\n", Phillips.IsPoweredOn());
		printf("State: %s\n", Phillips.IsPoweredOn() ? "On" : "Off");
		printf("Volume: %.i Db\n", Phillips.GetIVolume());
		printf("Frequency: %.2f MHz\n", Phillips.GetFrequency());
		std::array<double, 5> frequencies = Phillips.GetInstalledFrequency();
		printf("Saved frequencies: %.2f MHz, %.2f MHz, %.2f MHz, %.2f MHz, %.2f MHz\n", frequencies[0], frequencies[1], frequencies[2], frequencies[3], frequencies[4]);
		printf("-----------------------------------------------------------------------------\n");
		printf("\n\n");
	}
	else if (radioNum == 1)
	{
		printf("-----------------------------------------------------------------------------\n");
		printf("-------------------------------State of Sony:--------------------------------\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("Power: %d\n", Sony.IsPoweredOn());
		printf("State: %s\n", Sony.IsPoweredOn() ? "On" : "Off");
		printf("Volume: %.i Db\n", Sony.GetIVolume());
		printf("Frequency: %.2f MHz\n", Sony.GetFrequency());
		std::array<double, 5> frequencies = Sony.GetInstalledFrequency();
		printf("Saved frequencies: %.2f MHz, %.2f MHz, %.2f MHz, %.2f MHz, %.2f MHz\n", frequencies[0], frequencies[1], frequencies[2], frequencies[3], frequencies[4]);
		printf("-----------------------------------------------------------------------------\n");
		printf("\n\n");
	}
}

// Перевірка збережень користувача
void CheckData(FM_Radio &Phillips, AM_Radio &Sony)
{
	std::string filename = DataManager::kFilename;
	bool is_file_exists = std::filesystem::exists(filename);
	if (is_file_exists)
	{
		char wantLoadSaveChar;
		while (true)
		{
			wantLoadSaveChar = GetChar("Do you want to load radio state from saves? [y - Yes; n - No] ");
			if (wantLoadSaveChar == ' ')
			{
				WarningMessage("Error. Please enter correct character [y - Yes; n - No] ");
			}
			else
			{
				break;
			}
		}
		if (wantLoadSaveChar == 'y')
		{
			if (!DataManager::LoadData(Phillips, Sony))
			{
				WarningMessage("Failed to load data from file.");
			}
		}
	}
	else
	{
		DataManager::CreateData();
	}
}