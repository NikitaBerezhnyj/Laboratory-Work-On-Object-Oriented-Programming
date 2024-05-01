#ifndef RADIO_HPP
#define RADIO_HPP

#include <array>
#include <stdlib.h>
#include <string.h>
#include <iostream>

class Radio
{
public:
  // Конструктори та деструктори
  Radio();
  Radio(bool is_powered_on, double frequency, int volume, std::array<double, 5> &installed_frequency);
  Radio(const Radio &other);
  ~Radio();

  // Методи
  void Reset();
  void TurnOn();
  void TurnOff();
  bool IsPoweredOn() const;
  void operator=(bool);
  virtual void SetFrequency(double frequency) = 0;
  double GetFrequency() const;
  void operator+=(double);
  void SetVolume(int volume);
  int GetIVolume() const;
  friend void operator-=(Radio &radio, int volume);
  void SetInstalledFrequency(std::array<double, 2> &value_and_index);
  std::array<double, 5> GetInstalledFrequency() const;
  void operator<<(std::array<double, 2> &value_and_index);
  void LoadFrequency(int index);

protected:
  bool is_powered_on_;
  double frequency_;
  int volume_;
  std::array<double, 5> installed_frequency_;

private:
  int max_volume = 120;
};

class FM_Radio : public Radio
{
public:
  FM_Radio();
  FM_Radio(bool is_powered_on, double frequency, int volume, std::array<double, 5> &installed_frequency);
  FM_Radio(const FM_Radio &other);
  ~FM_Radio();
  void SetFrequency(double frequency) override;

private:
  double min_lim = 87.5;
  double max_lim = 108.0;
};

class AM_Radio : public Radio
{
public:
  AM_Radio();
  AM_Radio(bool is_powered_on, double frequency, int volume, std::array<double, 5> &installed_frequency);
  AM_Radio(const AM_Radio &other);
  ~AM_Radio();
  void SetFrequency(double frequency) override;

private:
  double min_lim = 540.0;
  double max_lim = 1610.0;
};

#endif // RADIO_HPP