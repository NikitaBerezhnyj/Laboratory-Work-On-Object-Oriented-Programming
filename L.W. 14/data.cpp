#include "data.hpp"
#include "radio.hpp"

const std::string DataManager::kFilename = "radio_data.bin";

bool DataManager::SaveData(const FM_Radio &Phillips, const AM_Radio &Sony, int radioNum)
{
    std::ofstream RadioData(kFilename, std::ios::binary);
    if (!RadioData)
    {
        std::cerr << "Error opening file for writing." << std::endl;
        return false;
    }

    if (radioNum == 0)
    {
        RadioData.write(reinterpret_cast<const char *>(&Phillips), sizeof(FM_Radio));
        RadioData.write(reinterpret_cast<const char *>(&Sony), sizeof(AM_Radio));
    }

    RadioData.close();
    return true;
}

bool DataManager::LoadData(FM_Radio &Phillips, AM_Radio &Sony)
{
    std::ifstream RadioData(kFilename, std::ios::binary);
    if (!RadioData)
    {
        std::cerr << "Error opening file for reading." << std::endl;
        return false;
    }

    RadioData.read(reinterpret_cast<char *>(&Phillips), sizeof(FM_Radio));
    RadioData.read(reinterpret_cast<char *>(&Sony), sizeof(AM_Radio));

    RadioData.close();
    return true;
}

void DataManager::CreateData()
{
    std::ofstream RadioData(kFilename);
    RadioData.close();
}