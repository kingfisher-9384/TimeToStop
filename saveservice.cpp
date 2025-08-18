#include "saveservice.hh"
#include <fstream>
#include <vector>


SaveService::SaveService()
{}


bool SaveService::save_time(int hours, int minutes)
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

    file << hourz << minutez << std::endl;
    file.close();

    return true;
}


std::string SaveService::read_time()
{
    //if (file_exists())
    //{
        std::fstream file;
        file.open("data/saves.json", std::ios::in);

        std::vector<std::string> lines;
        std::string temp_line;

        while (getline(file, temp_line))
        {
            if (temp_line.length() > 0)
            {
                lines.push_back(temp_line);
            }
        }

        return lines[0];
    //}
    //else
        //return "balls";
}


//bool SaveService::file_exists()
