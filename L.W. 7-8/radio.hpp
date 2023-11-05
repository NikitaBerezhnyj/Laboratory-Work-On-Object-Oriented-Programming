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
      void SetFrequency(double frequency);
      double GetFrequency() const;

      // Управління частотою через оператор +=
      void operator += (double);

      // Управління гучністю
      void SetVolume(int volume);
      int GetIVolume() const;

      // Управління гучністю через оператор -=
      friend void operator -=(Radio& radio, int volume);

      // Управління збереженими частотами
      // void SetInstalledFrequency(double value, int index);
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