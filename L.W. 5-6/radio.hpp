// Типи радіоприймачів
enum class RadioRange {
  FM_Short,
  FM_Medium,
  FM_Long,
  AM_Short,
  AM_Medium,
  AM_Long,
  SW,
  LW
};

// Типи портів радіоприймачів
enum class RadioPort {
  AM,
  FM,
  SW,
  LW
};

// Типи антен радіоприймачів
enum class RadioAntenna {
  Omnidirectional,
  Yagi,
  Dish
};

class Radio
{
    public:
        // Конструктор за замовчуванням
        Radio();

        // Конструктор ініціалізації з самостійно визначеними аргументами
        Radio(bool is_powered_on, double frequency, float output_power,
              RadioRange range, float sensitivity, float impedance,
              float signal_to_noise_ratio, int number_of_channels,
              RadioPort ports, RadioAntenna antenna);

        // Конструктор копіювання
        Radio(const Radio& other);

        // Дестриуктор
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

        // Управління вихідною потужністю
        void SetOutputPower(float output_power);
        float GetOutputPower() const;

        // Управління дальністю дії
        void SetRange(RadioRange range);
        RadioRange GetRange() const;

        // Управління чутливістю
        void SetSensitivity(float sensitivity);
        float GetSensitivity() const;

        // Управління імпедансом антени
        void SetImpedance(float impedance);
        float GetImpedance() const;

        // Управління імпедансом антени через оператор -=
        friend void operator-=(Radio& radio, float impedance);

        // Управління співвідношенням сигнал/шум
        void SetSignalToNoiseRatio(float signal_to_noise_ratio);
        float GetSignalToNoiseRatio() const;

        // Управління співвідношення сигнал/шум оператором ==
        void operator==(float signal_to_noise_ratio);

        // Управління кількістю каналів
        void SetNumberOfChannels(int number_of_channels);
        int GetNumberOfChannels() const;

        // Управління типом портів
        void SetPorts(RadioPort ports);
        RadioPort GetPorts() const;

        // Управління типом антени
        void SetAntenna(RadioAntenna antenna);
        RadioAntenna GetAntenna() const;

        // Конвертація enum в string
        std::string GetPortsAsString() const;
        std::string GetAntennaAsString() const;
        std::string GetRangeAsString() const;

    private:
        bool is_powered_on_;
        double frequency_;
        float output_power_;
        RadioRange range_;
        float sensitivity_;
        float impedance_;
        float signal_to_noise_ratio_;
        int number_of_channels_;
        RadioPort ports_;
        RadioAntenna antenna_;
};