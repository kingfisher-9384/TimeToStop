#include "saveservice.hh"
#include <QDir>


SaveService::SaveService()
{}


bool SaveService::saveTime()
{

    if (!QDir("ProgramData/saves").exists())
    {
        QDir().mkdir("ProgramData/saves");

        // doesn't fucking work!!


    }

    std::fstream file;
    file.open("saves.json", )
        // try to open in fstream so r and w or then just open and close accordingly



    return true;
}
