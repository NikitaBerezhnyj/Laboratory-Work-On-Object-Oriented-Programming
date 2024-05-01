#include "users.hpp"

// Клас користувач
User::User() : FM_Radio(), AM_Radio() {}

User::User(bool is_powered_on, double frequency, int volume, std::array<double, 5> &installed_frequency)
    : FM_Radio(is_powered_on, frequency, volume, installed_frequency),
      AM_Radio(is_powered_on, frequency, volume, installed_frequency) {}

User::User(const User &other)
    : FM_Radio(static_cast<const FM_Radio &>(other)), AM_Radio(static_cast<const AM_Radio &>(other)) {}

void User::FM_TurnOn(FM_Radio &fm_radio)
{
    fm_radio.TurnOn();
}

void User::FM_TurnOff(FM_Radio &fm_radio)
{
    fm_radio.TurnOff();
}

void User::FM_ChangeFrequency(FM_Radio &fm_radio, double frequency_)
{
    fm_radio.SetFrequency(frequency_);
}

void User::FM_ChangeVolume(FM_Radio &fm_radio, int volume_)
{
    fm_radio.SetVolume(volume_);
}

void User::FM_SaveFrequency(FM_Radio &fm_radio, std::array<double, 2> installed_frequency_)
{
    std::array<double, 2> value_and_index = {installed_frequency_[0], installed_frequency_[1]};
    fm_radio.SetInstalledFrequency(value_and_index);
}

void User::FM_LoadFrequency(FM_Radio &fm_radio, int index_)
{
    fm_radio.LoadFrequency(index_);
}

void User::AM_TurnOn(AM_Radio &am_radio)
{
    am_radio.TurnOn();
}

void User::AM_TurnOff(AM_Radio &am_radio)
{
    am_radio.TurnOff();
}

void User::AM_ChangeFrequency(AM_Radio &am_radio, double frequency_)
{
    am_radio.SetFrequency(frequency_);
}

void User::AM_ChangeVolume(AM_Radio &am_radio, int volume_)
{
    am_radio.SetVolume(volume_);
}

void User::AM_SaveFrequency(AM_Radio &am_radio, std::array<double, 2> installed_frequency_)
{
    std::array<double, 2> value_and_index = {installed_frequency_[0], installed_frequency_[1]};
    am_radio.SetInstalledFrequency(value_and_index);
}

void User::AM_LoadFrequency(AM_Radio &am_radio, int index_)
{
    am_radio.LoadFrequency(index_);
}

// Клас адміністратор
Admin::Admin() : User() {}

Admin::Admin(bool is_powered_on, double frequency, int volume, std::array<double, 5> &installed_frequency)
    : User(is_powered_on, frequency, volume, installed_frequency) {}

Admin::Admin(const Admin &other) : User(static_cast<const User &>(other)) {}

void Admin::FM_TurnOn(FM_Radio &fm_radio)
{
    fm_radio.TurnOn();
}

void Admin::FM_TurnOff(FM_Radio &fm_radio)
{
    fm_radio.TurnOff();
}

void Admin::AM_TurnOn(AM_Radio &am_radio)
{
    am_radio.TurnOn();
}

void Admin::AM_TurnOff(AM_Radio &am_radio)
{
    am_radio.TurnOff();
}

// Клас менеджер
Manager::Manager() : User() {}

Manager::Manager(bool is_powered_on, double frequency, int volume, std::array<double, 5> &installed_frequency)
    : User(is_powered_on, frequency, volume, installed_frequency) {}

Manager::Manager(const Manager &other) : User(static_cast<const User &>(other)) {}

void Manager::FM_SaveFrequency(FM_Radio &fm_radio, std::array<double, 2> installed_frequency_)
{
    std::array<double, 2> value_and_index = {installed_frequency_[0], installed_frequency_[1]};
    fm_radio.SetInstalledFrequency(value_and_index);
}

void Manager::FM_LoadFrequency(FM_Radio &fm_radio, int index_)
{
    fm_radio.LoadFrequency(index_);
}

void Manager::AM_SaveFrequency(AM_Radio &am_radio, std::array<double, 2> installed_frequency_)
{
    std::array<double, 2> value_and_index = {installed_frequency_[0], installed_frequency_[1]};
    am_radio.SetInstalledFrequency(value_and_index);
}

void Manager::AM_LoadFrequency(AM_Radio &am_radio, int index_)
{
    am_radio.LoadFrequency(index_);
}

// Клас директор
Director::Director() : User() {}

Director::Director(bool is_powered_on, double frequency, int volume, std::array<double, 5> &installed_frequency)
    : User(is_powered_on, frequency, volume, installed_frequency) {}
Director::Director(const Director &other) : User(static_cast<const User &>(other)) {}
void Director::FM_ChangeFrequency(FM_Radio &fm_radio, double frequency_)
{
    fm_radio.SetFrequency(frequency_);
}
void Director::FM_ChangeVolume(FM_Radio &fm_radio, int volume_)
{
    fm_radio.SetVolume(volume_);
}
void Director::AM_ChangeFrequency(AM_Radio &am_radio, double frequency_)
{
    am_radio.SetFrequency(frequency_);
}
void Director::AM_ChangeVolume(AM_Radio &am_radio, int volume_)
{
    am_radio.SetVolume(volume_);
}