// _________________________________________
// Користувач
// _________________________________________

switch (key)
{
    case 0:
        if (radioNum == 0)
        {
            Phillips.TurnOff();
            // Phillips = false;
        }
        else if (radioNum == 1)
        {
            Transistorola.TurnOff();
            // Transistorola = false;
        }              
        break;
    case 1:
        if (radioNum == 0)
        {
            Phillips.TurnOn();
            // Phillips = true;
        }
        else if (radioNum == 1)
        {
            Transistorola.TurnOn();
            // Transistorola = true;
        }
        break;
    case 2: 
        double frequency;
        cout << "Enter frequency (MHz): ";
        cin >> frequency;
        if (radioNum == 0)
        {
            // Phillips.SetFrequency(frequency);
            Phillips += frequency;
        }
        else if (radioNum == 1)
        {
            // Transistorola.SetFrequency(frequency);
            Transistorola += frequency;
        }
        break;
    case 3: 
        double volume;
        cout << "Enter volume (db): ";
        cin >> volume;
        if (radioNum == 0)
        {
            // Phillips.SetVolume(volume);
            Phillips -= volume;
        }
        else if (radioNum == 1)
        {
            // Transistorola.SetVolume(volume);
            Transistorola -= volume;
        }
        break;
    case 4:
        int index;
        double value;
        cout << "Enter index for saving this frequency: ";
        cin >> index;
        cout << "Enter frequency for saving: ";
        cin >> value;
        std::array<double, 2> value_and_index;
        value_and_index[0] = value;
        value_and_index[1] = index;
        if (radioNum == 0)
        {
            // Phillips.SetInstalledFrequency(value_and_index);
            Phillips << value_and_index;
        }
        else if (radioNum == 1)
        {
            // Transistorola.SetInstalledFrequency(value_and_index);
            Transistorola << value_and_index;
        }
        break;
    case 5:
        cout << "Select radio (0 - Phillips, 1 - Transistorola): ";
        cin >> radioNum;
        break;
    case 6: 
        Phillips.~FM_Radio();
        Phillips.~FM_Radio();
        Transistorola.~AM_Radio();
        Transistorola.~AM_Radio();
        cout << "All objects have been delated\n";
        is_work = false;
        break;
    case 7: 
        is_work = false;
        break;
    default: 
        cout << "Looks like you made a mistake" << endl;
        break;
}

// _________________________________________
// Адміністратор
// _________________________________________