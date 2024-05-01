#ifndef USERS_HPP
#define USERS_HPP

#include "radio.hpp"

class User : public FM_Radio, public AM_Radio
{
public:
    User();
    User(bool is_powered_on, double frequency, int volume, std::array<double, 5> &installed_frequency);
    User(const User &other);

    // Методи
    void FM_TurnOn(FM_Radio &fm_radio);
    void FM_TurnOff(FM_Radio &fm_radio);
    void FM_ChangeFrequency(FM_Radio &fm_radio, double frequency_);
    void FM_ChangeVolume(FM_Radio &fm_radio, int volume_);
    void FM_SaveFrequency(FM_Radio &fm_radio, std::array<double, 2> installed_frequency_);
    void FM_LoadFrequency(FM_Radio &fm_radio, int index_);
    void AM_TurnOn(AM_Radio &am_radio);
    void AM_TurnOff(AM_Radio &am_radio);
    void AM_ChangeFrequency(AM_Radio &am_radio, double frequency_);
    void AM_ChangeVolume(AM_Radio &am_radio, int volume_);
    void AM_SaveFrequency(AM_Radio &am_radio, std::array<double, 2> installed_frequency_);
    void AM_LoadFrequency(AM_Radio &am_radio, int index_);

protected:
    bool is_powered_on_;
    double frequency_;
    int volume_;
    std::array<double, 5> installed_frequency_;
};

class Admin : public User
{
public:
    Admin();
    Admin(bool is_powered_on, double frequency, int volume, std::array<double, 5> &installed_frequency);
    Admin(const Admin &other);

    void FM_TurnOn(FM_Radio &fm_radio);
    void FM_TurnOff(FM_Radio &fm_radio);
    void AM_TurnOn(AM_Radio &am_radio);
    void AM_TurnOff(AM_Radio &am_radio);

protected:
    bool is_powered_on_;
};

class Manager : public User
{
public:
    Manager();
    Manager(bool is_powered_on, double frequency, int volume, std::array<double, 5> &installed_frequency);
    Manager(const Manager &other);

    void FM_SaveFrequency(FM_Radio &fm_radio, std::array<double, 2> installed_frequency_);
    void AM_SaveFrequency(AM_Radio &am_radio, std::array<double, 2> installed_frequency_);

    void FM_LoadFrequency(FM_Radio &fm_radio, int index_);
    void AM_LoadFrequency(AM_Radio &am_radio, int index_);

protected:
    std::array<double, 5> installed_frequency_;
};

class Director : public User
{
public:
    Director();
    Director(bool is_powered_on, double frequency, int volume, std::array<double, 5> &installed_frequency);
    Director(const Director &other);

    void FM_ChangeFrequency(FM_Radio &fm_radio, double frequency_);
    void FM_ChangeVolume(FM_Radio &fm_radio, int volume_);
    void AM_ChangeFrequency(AM_Radio &am_radio, double frequency_);
    void AM_ChangeVolume(AM_Radio &am_radio, int volume_);

protected:
    double frequency_;
    int volume_;
};

#endif // USERS_HPP