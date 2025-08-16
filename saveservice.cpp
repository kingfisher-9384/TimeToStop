#include "saveservice.hh"


SaveService::SaveService()
{}


bool SaveService::saveTime(int hours, int minutes)
{

    if (!QDir("data").exists())
    {
        QDir().mkdir("data");
    }

    std::fstream file;
    file.open("data/saves.json", std::ios::out);


    std::string hourz = std::to_string(hours);
    std::string minutez = std::to_string(minutes);
    if (hours < 10)
        hourz = "0" + hourz;
    if (minutes < 10)
        minutez = "0" + minutez;


    file << hourz << minutez << std::endl; // append flag


    return true;
}
