#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "radio.hpp"

using namespace std;

// Батьківський клас Radio
Radio::Radio() :
  is_powered_on_(false),
  frequency_(100.0),
  volume_(10),
  installed_frequency_()
{}
// Конструктор ініціалізації з самостійно визначеними аргументами
Radio::Radio(bool is_powered_on, double frequency, int volume, std::array<double, 5>& installed_frequency):
  is_powered_on_(is_powered_on), 
  frequency_(frequency), 
  volume_(volume), 
  installed_frequency_(installed_frequency)
{}
// Конструктор копіювання
Radio::Radio(const Radio& other) :
  is_powered_on_(other.is_powered_on_),
  frequency_(other.frequency_),
  volume_(other.volume_), 
  installed_frequency_(other.installed_frequency_)
{}
// Деструктор
Radio::~Radio() {}
void Radio::Reset (void)
{
	is_powered_on_ = false;
  frequency_= 100.0;
  volume_ = 10;
  installed_frequency_ = {0, 0, 0, 0, 0};
}
// Управління живленням
void Radio::TurnOn() {
  is_powered_on_ = true;
}
void Radio::TurnOff() {
  is_powered_on_ = false;
}
bool Radio::IsPoweredOn() const {
  return is_powered_on_;
}
void Radio::operator = (bool State)
{
  State ? TurnOn () : TurnOff ();
}
// Управління частотою
// void Radio::SetFrequency(double frequency)
// { 
//   frequency_ = frequency;
// }
double Radio::GetFrequency() const {
  return frequency_;
}
void Radio::operator += (double frequency)
{
  frequency_ = frequency;
}
// Управління гучністю
void Radio::SetVolume(int volume)
{ 
  if (volume <= 0)
  {
    volume = 0;
  }
  volume_ = volume;
}
int Radio::GetIVolume() const {
  return volume_;
}
void operator-=(Radio& radio, int volume)
{
  if (volume <= 0)
  {
    volume = 0;
  }
  radio.volume_ = volume;
}
// Управління збереженими частотами
void Radio::SetInstalledFrequency(std::array<double, 2>& value_and_index)
{
  int index = static_cast<int>(value_and_index[1]);
  double value = value_and_index[0];
  if (index >= 0 && index < installed_frequency_.size())
  {
    installed_frequency_[index] = value;    
  }
  else
  {
    std::cout << "Invalid index: " << index << std::endl;
  }
}

std::array<double, 5> Radio::GetInstalledFrequency() const
{
    return installed_frequency_;
}
void Radio::operator << (std::array<double, 2>& value_and_index)
{
    double value = value_and_index[0];
    int index = value_and_index[1];
    if (index >= 0 && index < installed_frequency_.size())
    {
        installed_frequency_[index] = value;
    }
}

// Підклас FM_Radio
// Конструктор за замовчуванням
FM_Radio::FM_Radio() : Radio()
{
  is_powered_on_ = false;
  frequency_= 87.5;
  volume_ = 10;
  installed_frequency_ = {0, 0, 0, 0, 0};
  min_lim = 87.5;
  max_lim = 108.0;
}
// Конструктор ініціалізації з самостійно визначеними аргументами
FM_Radio::FM_Radio(bool is_powered_on, double frequency, int volume, std::array<double, 5>& installed_frequency) :
  Radio(is_powered_on, frequency, volume, installed_frequency),
  min_lim(87.5),
  max_lim(108.0)
{}
// Конструктор копіювання
FM_Radio::FM_Radio(const FM_Radio& other) :
  Radio(other),
  min_lim(other.min_lim),
  max_lim(other.max_lim)
{}
// Деструктор
FM_Radio::~FM_Radio() {}
// Перевантаження методу SetFrequency для FM хвиль
void FM_Radio::SetFrequency(double frequency)
{ 
  if (frequency > min_lim && frequency < max_lim)
  {
    frequency_ = frequency;
  }
  else
  {
    cout << "Frequency goes beyond AM waves" << endl;
  }
}

// Підклас AM_Radio
AM_Radio::AM_Radio() : Radio()
{
  is_powered_on_ = false;
  frequency_= 540.0;
  volume_ = 15;
  installed_frequency_ = {0, 0, 0, 0, 0};
  min_lim = 540.0;
  max_lim = 1600.0;
}
// Конструктор ініціалізації з самостійно визначеними аргументами
AM_Radio::AM_Radio(bool is_powered_on, double frequency, int volume, std::array<double, 5>& installed_frequency) :
  Radio(is_powered_on, frequency, volume, installed_frequency),
  min_lim(87.5),
  max_lim(108.0)
{}
// Конструктор копіювання
AM_Radio::AM_Radio(const AM_Radio& other) :
  Radio(other),
  min_lim(other.min_lim),
  max_lim(other.max_lim)
{}
// Деструктор
AM_Radio::~AM_Radio() {}
// Перевантаження методу SetFrequency для AM хвиль
void AM_Radio::SetFrequency(double frequency)
{ 
  if (frequency > min_lim && frequency < max_lim)
  {
    frequency_ = frequency;
  }
  else
  {
    cout << "Frequency goes beyond AM waves" << endl;
  }
}

// Користувач
// Увімкнути об'єкт FM_Radio
void User::FM_TurnOn(FM_Radio& fm_radio)
{
  fm_radio.TurnOn();
}
// Вимкнути об'єкт FM_Radio
void User::FM_TurnOff(FM_Radio& fm_radio)
{
  fm_radio.TurnOff();
}
// Змінити частоту на об'єкті FM_Radio
void User::FM_ChangeFrequency(FM_Radio& fm_radio, double frequency_)
{
  fm_radio.SetFrequency(frequency_);
}
// Змінити гучність на об'єкті FM_Radio
void User::FM_ChangeVolume(FM_Radio& fm_radio, int volume_)
{
  fm_radio.SetVolume(volume_);
}
// Зберегти частоту в об'єкті FM_Radio
void User::FM_SaveFrequency(FM_Radio& fm_radio, std::array<double, 2> installed_frequency_)
{
  std::array<double, 2> value_and_index = {installed_frequency_[0], installed_frequency_[1]};
  fm_radio.SetInstalledFrequency(value_and_index);
}
// Увімкнути об'єкт AM_Radio
void User::AM_TurnOn(AM_Radio& am_radio)
{
  am_radio.TurnOn();
}
// Вимкнути об'єкт AM_Radio
void User::AM_TurnOff(AM_Radio& am_radio)
{
  am_radio.TurnOff();
}
// Змінити частоту на об'єкті AM_Radio
void User::AM_ChangeFrequency(AM_Radio& am_radio, double frequency_)
{
  am_radio.SetFrequency(frequency_);
}
// Змінити гучність на об'єкті AM_Radio
void User::AM_ChangeVolume(AM_Radio& am_radio, int volume_)
{
  am_radio.SetVolume(volume_);
}
// Зберегти частоту в об'єкті AM_Radio
void User::AM_SaveFrequency(AM_Radio& am_radio, std::array<double, 2> installed_frequency_)
{
  std::array<double, 2> value_and_index = {installed_frequency_[0], installed_frequency_[1]};
  am_radio.SetInstalledFrequency(value_and_index);
}

// Адміністратор
// Увімкнути об'єкт FM_Radio
void Admin::FM_TurnOn(FM_Radio& fm_radio)
{
  fm_radio.TurnOn();
}
// Вимкнути об'єкт FM_Radio
void Admin::FM_TurnOff(FM_Radio& fm_radio)
{
  fm_radio.TurnOff();
}
// Увімкнути об'єкт AM_Radio
void Admin::AM_TurnOn(AM_Radio& am_radio)
{
  am_radio.TurnOn();
}
// Вимкнути об'єкт AM_Radio
void Admin::AM_TurnOff(AM_Radio& am_radio)
{
  am_radio.TurnOff();
}

// Менеджер
// Зберегти частоту в об'єкті FM_Radio
void Manager::FM_SaveFrequency(FM_Radio& fm_radio, std::array<double, 2> installed_frequency_)
{
  std::array<double, 2> value_and_index = {installed_frequency_[0], installed_frequency_[1]};
  fm_radio.SetInstalledFrequency(value_and_index);
}
// Зберегти частоту в об'єкті FM_Radio
void Manager::AM_SaveFrequency(AM_Radio& am_radio, std::array<double, 2> installed_frequency_)
{
  std::array<double, 2> value_and_index = {installed_frequency_[0], installed_frequency_[1]};
  am_radio.SetInstalledFrequency(value_and_index);
}

// Керівник
// Змінити частоту на об'єкті FM_Radio
void Director::FM_ChangeFrequency(FM_Radio& fm_radio, double frequency_)
{
  fm_radio.SetFrequency(frequency_);
}
// Змінити гучність на об'єкті FM_Radio
void Director::FM_ChangeVolume(FM_Radio& fm_radio, int volume_)
{
  fm_radio.SetVolume(volume_);
}
// Змінити частоту на об'єкті AM_Radio
void Director::AM_ChangeFrequency(AM_Radio& am_radio, double frequency_)
{
  am_radio.SetFrequency(frequency_);
}
// Змінити гучність на об'єкті AM_Radio
void Director::AM_ChangeVolume(AM_Radio& am_radio, int volume_)
{
  am_radio.SetVolume(volume_);
}