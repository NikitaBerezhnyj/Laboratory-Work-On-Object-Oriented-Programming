#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

class FM_Radio;
class AM_Radio;

class DataManager
{
public:
    static const std::string kFilename;
    static void CreateData();
    static bool SaveData(const FM_Radio &Phillips, const AM_Radio &Sony, int radioNum);
    static bool LoadData(FM_Radio &Phillips, AM_Radio &Sony);
};

#endif // DATA_HPP