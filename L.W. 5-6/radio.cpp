#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "radio.hpp"

using namespace std;

Radio::Radio() :
  is_powered_on_(false),
  frequency_(100.0),
  output_power_(100.0),
  range_(RadioRange::FM_Short),
  sensitivity_(100.0),
  impedance_(100.0),
  signal_to_noise_ratio_(100.0),
  number_of_channels_(100),
  ports_(RadioPort::FM),
  antenna_(RadioAntenna::Omnidirectional)
{}

// Конструктор ініціалізації з самостійно визначеними аргументами
Radio::Radio(bool is_powered_on, double frequency, float output_power, 
                  RadioRange range, float sensitivity, float impedance, 
                  float signal_to_noise_ratio, int number_of_channels, 
                  RadioPort ports, RadioAntenna antenna):
  is_powered_on_(is_powered_on),
  frequency_(frequency),
  output_power_(output_power),
  range_(range),
  sensitivity_(sensitivity),
  impedance_(impedance),
  signal_to_noise_ratio_(signal_to_noise_ratio),
  number_of_channels_(number_of_channels),
  ports_(ports),
  antenna_(antenna)
{}

// Конструктор копіювання
Radio::Radio(const Radio& other) :
  is_powered_on_(other.is_powered_on_),
  frequency_(other.frequency_),
  output_power_(other.output_power_),
  range_(other.range_),
  sensitivity_(other.sensitivity_),
  impedance_(other.impedance_),
  signal_to_noise_ratio_(other.signal_to_noise_ratio_),
  number_of_channels_(other.number_of_channels_),
  ports_(other.ports_),
  antenna_(other.antenna_)
{}

Radio::~Radio() {}

void Radio::Reset (void)
{
    is_powered_on_ = false;
    frequency_ = 100.0;
    output_power_ = 100.0;
    range_ = RadioRange::FM_Short;
    sensitivity_ = 100.0;
    impedance_ = 100.0;
    signal_to_noise_ratio_ = 100.0;
    number_of_channels_ = 100;
    ports_ = RadioPort::FM;
    antenna_ = RadioAntenna::Omnidirectional;
}

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

void Radio::SetFrequency(double frequency) {
  switch (range_) {
    case RadioRange::FM_Short:
      if (frequency < 64 || frequency > 108) {
        cout << "Frequency out of range for FM Short (64 - 108 MHz)." << endl;
        return;
      }
      break;
    case RadioRange::FM_Medium:
      if (frequency < 530 || frequency > 1710) {
        cout << "Frequency out of range for FM Medium (530 - 1710 MHz)." << endl;
        return;
      }
      break;
    case RadioRange::FM_Long:
      if (frequency < 300 || frequency > 340) {
        cout << "Frequency out of range for FM Long (300 - 340 MHz)." << endl;
        return;
      }
      break;
    case RadioRange::AM_Short:
      if (frequency < 530.0 || frequency > 1700.0) {
        cout << "Frequency out of range for AM Short (530 - 1700 kHz)." << endl;
        return;
      }
      break;

    case RadioRange::AM_Medium:
      if (frequency < 530 || frequency > 1710) {
        cout << "Frequency out of range for FM Long (530 - 1710 MHz)." << endl;
        return;
      }
      break;
    case RadioRange::AM_Long:
      if (frequency < 1605 || frequency > 1800) {
        cout << "Frequency out of range for FM Long (1605 - 1800 MHz)." << endl;
        return;
      }
    case RadioRange::SW:
      if (frequency < 3 || frequency > 30) {
        cout << "Frequency out of range for FM Long (3 - 30 MHz)." << endl;
        return;
      }
    case RadioRange::LW:
      if (frequency < 148 || frequency > 283) {
        cout << "Frequency out of range for FM Long (148 - 283 MHz)." << endl;
        return;
      }
    default:
      cout << "Unknown range. Frequency change not allowed." << endl;
      return;
  }
  
  frequency_ = frequency;
}

double Radio::GetFrequency() const {
  return frequency_;
}

void Radio::operator += (double frequency)
{
  switch (range_) {
    case RadioRange::FM_Short:
      if (frequency < 64 || frequency > 108) {
        cout << "Frequency out of range for FM Short (64 - 108 MHz)." << endl;
        return;
      }
      break;
    case RadioRange::FM_Medium:
      if (frequency < 530 || frequency > 1710) {
        cout << "Frequency out of range for FM Medium (530 - 1710 MHz)." << endl;
        return;
      }
      break;
    case RadioRange::FM_Long:
      if (frequency < 300 || frequency > 340) {
        cout << "Frequency out of range for FM Long (300 - 340 MHz)." << endl;
        return;
      }
      break;
    case RadioRange::AM_Short:
      if (frequency < 530.0 || frequency > 1700.0) {
        cout << "Frequency out of range for AM Short (530 - 1700 kHz)." << endl;
        return;
      }
      break;

    case RadioRange::AM_Medium:
      if (frequency < 530 || frequency > 1710) {
        cout << "Frequency out of range for FM Long (530 - 1710 MHz)." << endl;
        return;
      }
      break;
    case RadioRange::AM_Long:
      if (frequency < 1605 || frequency > 1800) {
        cout << "Frequency out of range for FM Long (1605 - 1800 MHz)." << endl;
        return;
      }
    case RadioRange::SW:
      if (frequency < 3 || frequency > 30) {
        cout << "Frequency out of range for FM Long (3 - 30 MHz)." << endl;
        return;
      }
    case RadioRange::LW:
      if (frequency < 148 || frequency > 283) {
        cout << "Frequency out of range for FM Long (148 - 283 MHz)." << endl;
        return;
      }
    default:
      cout << "Unknown range. Frequency change not allowed." << endl;
      return;
  }
  
  frequency_ = frequency;
}

void Radio::SetOutputPower(float output_power) {
  if (output_power < 12) {
    TurnOff();
    return;
  }
  if (output_power > 500) {
    TurnOff();
    return;
  }
  output_power_ = output_power;
}

float Radio::GetOutputPower() const {
  return output_power_;
}

void Radio::SetRange(RadioRange range) {
  range_ = range;
}

RadioRange Radio::GetRange() const {
  return range_;
}

void Radio::SetSensitivity(float sensitivity) {
  sensitivity_ = sensitivity;
}

float Radio::GetSensitivity() const {
  return sensitivity_;
}

void Radio::SetImpedance(float impedance) {
  impedance_ = impedance;
}

float Radio::GetImpedance() const {
  return impedance_;
}

void operator-=(Radio& radio, float impedance) {
    radio.impedance_ = impedance;
}

void Radio::SetSignalToNoiseRatio(float signal_to_noise_ratio) {
  signal_to_noise_ratio_ = signal_to_noise_ratio;
}

float Radio::GetSignalToNoiseRatio() const {
  return signal_to_noise_ratio_;
}

void Radio::operator==(float signal_to_noise_ratio)
{
  signal_to_noise_ratio_ = signal_to_noise_ratio;
}

void Radio::SetNumberOfChannels(int number_of_channels) {
  number_of_channels_ = number_of_channels;
}

int Radio::GetNumberOfChannels() const {
  return number_of_channels_;
}

void Radio::SetPorts(RadioPort ports) {
  if (is_powered_on_) {
    cout << "Cannot change ports while the radio is powered on." << endl;
    return;
  }
  ports_ = ports;
}

RadioPort Radio::GetPorts() const {
  return ports_;
}

void Radio::SetAntenna(RadioAntenna antenna) {
  if (is_powered_on_) {
    cout << "Cannot change antenna while the radio is powered on." << endl;
    return;
  }
  antenna_ = antenna;
}

RadioAntenna Radio::GetAntenna() const {
  return antenna_;
}

std::string Radio::GetPortsAsString() const {
  switch (ports_) {
    case RadioPort::AM:
      return "AM";
    case RadioPort::FM:
      return "FM";
    case RadioPort::SW:
      return "SW";
    case RadioPort::LW:
      return "LW";
    default:
      return "Unknown";
  }
}

std::string Radio::GetAntennaAsString() const {
  switch (antenna_) {
    case RadioAntenna::Omnidirectional:
      return "Omnidirectional";
    case RadioAntenna::Yagi:
      return "Yagi";
    case RadioAntenna::Dish:
      return "Dish";
    default:
      return "Unknown";
  }
}

std::string Radio::GetRangeAsString() const {
  switch (range_) {
    case RadioRange::FM_Short:
      return "FM Short";
    case RadioRange::FM_Medium:
      return "FM Medium";
    case RadioRange::FM_Long:
      return "FM Long";
    case RadioRange::AM_Short:
      return "AM Short";
    case RadioRange::AM_Medium:
      return "AM Medium";
    case RadioRange::AM_Long:
      return "AM Long";
    case RadioRange::SW:
      return "SW";
    case RadioRange::LW:
      return "LW";
    default:
      return "Unknown";
  }
}