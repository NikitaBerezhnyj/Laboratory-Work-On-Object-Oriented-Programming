#include <string>
#include <array>

using namespace std;

// Батьківський клас Radio
class Radio
{
    public:
      // Конструктор за замовчуванням
      Radio();
      // Конструктор ініціалізації з самостійно визначеними аргументами
      Radio(bool is_powered_on, double frequency, int volume, std::array<double, 5>& installed_frequency);
      // Конструктор копіювання
      Radio(const Radio& other);
      // Деструктор
      ~Radio();
      // Стандартні налаштування будь якого радіо
      void Reset();
      // Управління живленням
      void TurnOn();
      void TurnOff();
      bool IsPoweredOn() const;
      // Управління живленням через оператор =
      void operator = (bool);
      // Управління частотою
      virtual void SetFrequency(double frequency) = 0;
      double GetFrequency() const;
      // Управління частотою через оператор +=
      void operator += (double);
      // Управління гучністю
      void SetVolume(int volume);
      int GetIVolume() const;
      // Управління гучністю через оператор -=
      friend void operator -=(Radio& radio, int volume);
      // Управління збереженими частотами
      void SetInstalledFrequency(std::array<double, 2>& value_and_index);
      std::array<double, 5> GetInstalledFrequency() const;
      // Управління збереженими частотами оператором ==
      void operator << (std::array<double, 2>& value_and_index);
    protected:
      bool is_powered_on_;
      double frequency_;
      int volume_;
      std::array<double, 5> installed_frequency_;
};

// Підклас FM Radio
class FM_Radio:public Radio
{
  public:
    // Конструктор за замовчуванням
    FM_Radio();
    // Конструктор ініціалізації з самостійно визначеними аргументами
    FM_Radio(bool is_powered_on, double frequency, int volume, std::array<double, 5>& installed_frequency);
    // Конструктор копіювання
    FM_Radio(const FM_Radio& other);
    // Деструктор
    ~FM_Radio();
    // Перевантаження методу SetFrequency для FM
    void SetFrequency(double frequency);
  private:
    double min_lim = 87.5;
    double max_lim = 108.0;
};

// Підклас AM Radio
class AM_Radio:public Radio
{
    public:
    // Конструктор за замовчуванням
    AM_Radio();
    // Конструктор ініціалізації з самостійно визначеними аргументами
    AM_Radio(bool is_powered_on, double frequency, int volume, std::array<double, 5>& installed_frequency);
    // Конструктор копіювання
    AM_Radio(const AM_Radio& other);
    // Деструктор
    ~AM_Radio();
    // Перевантаження методу SetFrequency для FM
    void SetFrequency(double frequency);
  private:
    double min_lim = 540.0;
    double max_lim = 1600.0;
};

// Користувач
class User:public FM_Radio, public AM_Radio
{
  public:
    // Конструктор за замовчуванням
    User() : FM_Radio(), AM_Radio() {}
    // Конструктор ініціалізації
    User(bool is_powered_on, double frequency, int volume, std::array<double, 5>& installed_frequency) : FM_Radio(is_powered_on, frequency, volume, installed_frequency), AM_Radio(is_powered_on, frequency, volume, installed_frequency) {}
    // Конструктор копіювання
    User(const User& other) : FM_Radio(static_cast<const FM_Radio&>(other)), AM_Radio(static_cast<const AM_Radio&>(other)) {}
    // Функції користувача
    // Увімкнути об'єкт FM_Radio
    void FM_TurnOn(FM_Radio& fm_radio);
    // Вимкнути об'єкт FM_Radio
    void FM_TurnOff(FM_Radio& fm_radio);
    // Змінити частоту на об'єкті FM_Radio
    void FM_ChangeFrequency(FM_Radio& fm_radio, double frequency_);
    // Змінити гучність на об'єкті FM_Radio
    void FM_ChangeVolume(FM_Radio& fm_radio, int volume_);
    // Зберегти частоту в об'єкті FM_Radio
    void FM_SaveFrequency(FM_Radio& fm_radio, std::array<double, 2> installed_frequency_);
    // Увімкнути об'єкт AM_Radio
    void AM_TurnOn(AM_Radio& am_radio);
    // Вимкнути об'єкт AM_Radio
    void AM_TurnOff(AM_Radio& am_radio);   
    // Змінити частоту на об'єкті AM_Radio
    void AM_ChangeFrequency(AM_Radio& am_radio, double frequency_);
    // Змінити гучність на об'єкті AM_Radio
    void AM_ChangeVolume(AM_Radio& am_radio, int volume_);
    // Зберегти частоту в об'єкті AM_Radio
    void AM_SaveFrequency(AM_Radio& am_radio, std::array<double, 2> installed_frequency_); 
  protected:
    bool is_powered_on_;
    double frequency_;
    int volume_;
    std::array<double, 5> installed_frequency_;
};
// Адміністратор
class Admin:public User
{
  public:
    // Конструктор за замовчуванням
    Admin() : User() {}
    // Конструктор ініціалізації
    Admin(bool is_powered_on, double frequency, int volume, std::array<double, 5>& installed_frequency) : User(is_powered_on, frequency, volume, installed_frequency) {}
    // Конструктор копіювання
    Admin(const Admin& other) : User(static_cast<const User&>(other)) {}
    // Функції адміністратора
    // Увімкнути об'єкт FM_Radio
    void FM_TurnOn(FM_Radio& fm_radio);
    // Вимкнути об'єкт FM_Radio
    void FM_TurnOff(FM_Radio& fm_radio);
    // Увімкнути об'єкт AM_Radio
    void AM_TurnOn(AM_Radio& am_radio);
    // Вимкнути об'єкт AM_Radio
    void AM_TurnOff(AM_Radio& am_radio);
  protected:
    bool is_powered_on_;
};
// Менеджер
class Manager:public User
{
  public:
    // Конструктор за замовчуванням
    Manager() : User() {}
    // Конструктор ініціалізації
    Manager(bool is_powered_on, double frequency, int volume, std::array<double, 5>& installed_frequency) : User(is_powered_on, frequency, volume, installed_frequency) {}
    // Конструктор копіювання
    Manager(const Manager& other) : User(static_cast<const User&>(other)) {}
    // Функції менеджера
    // Зберегти частоту в об'єкті FM_Radio
    void FM_SaveFrequency(FM_Radio& fm_radio, std::array<double, 2> installed_frequency_);
    // Зберегти частоту в об'єкті FM_Radio
    void AM_SaveFrequency(AM_Radio& am_radio, std::array<double, 2> installed_frequency_); 
  protected:
    std::array<double, 5> installed_frequency_;
};
// Керівник
class Director:public User
{
  public:
    // Конструктор за замовчуванням
    Director() : User() {}
    // Конструктор ініціалізації
    Director(bool is_powered_on, double frequency, int volume, std::array<double, 5>& installed_frequency) : User(is_powered_on, frequency, volume, installed_frequency) {}
    // Конструктор копіювання
    Director(const Director& other) : User(static_cast<const User&>(other)) {}
    // Функції директора
    // Змінити частоту на об'єкті FM_Radio
    void FM_ChangeFrequency(FM_Radio& fm_radio, double frequency_);
    // Змінити гучність на об'єкті FM_Radio
    void FM_ChangeVolume(FM_Radio& fm_radio, int volume_);
    // Змінити частоту на об'єкті AM_Radio
    void AM_ChangeFrequency(AM_Radio& am_radio, double frequency_);
    // Змінити гучність на об'єкті AM_Radio
    void AM_ChangeVolume(AM_Radio& am_radio, int volume_);
  protected:
    double frequency_;
    int volume_;
};