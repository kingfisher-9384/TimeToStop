#include "saveservice.hh"
//#include <sys/stat.h>
//#include <experimental/filesystem>
#include <fstream>
#include <vector>
#include <string>


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


std::pair<int,int> SaveService::read_time()
{
    std::pair<int,int> hour_and_min;

    if (file_exists())
    {
        qDebug() << "yay it worky";
        std::fstream file;
        file.open("data/saves.json", std::ios::in);

        std::vector<std::string> lines;
        std::string temp_line;

        while (getline(file, temp_line))
        {
            if (temp_line.length() > 0)
            {
                lines.push_back(temp_line);
                temp_line = "";
            }
        }
        hour_and_min = get_time_from_line(lines);

        file.close();
        return hour_and_min;
    }
    else
    {
        qDebug() << "no worky";
        save_time(DEFAULT_HOUR, DEFAULT_MINUTE);

        std::fstream file;
        file.open("data/saves.json", std::ios::in);

        std::vector<std::string> lines;
        std::string temp_line;

        while (getline(file, temp_line))
        {
            if (temp_line.length() > 0)
            {
                lines.push_back(temp_line);
                temp_line = "";
            }
        }
        hour_and_min = get_time_from_line(lines);

        file.close();
        return hour_and_min;
    }
}


bool SaveService::file_exists()
{
    /*const std::string& path = "data/saves.json";
    struct stat buffer;
    return (stat (path.c_str(), &buffer) == 0);*/

    return std::filesystem::exists("data/saves.json");  // maybe just chuck this into read_time
}


std::pair<int,int> SaveService::get_time_from_line(std::vector<std::string> lines)
{
    int hour;
    int minute;

    std::string time = lines[0];
    auto temp_string = std::string(1, time[0]) + time[1];
    hour = std::stoi(temp_string);
    temp_string = std::string(1, time[2]) + time[3];
    minute = std::stoi(temp_string);

    return (std::pair<int,int>(hour, minute));
}

bool SaveService::set_onoff(bool is_on)
{
    std::fstream file;
    file.open("data/saves.json");

    std::vector<std::string> lines;
    std::string temp_line;

    while (getline(file, temp_line))
    {
        if (temp_line.length() > 0)
        {
            lines.push_back(temp_line);
            temp_line = "";
        }
    }

    if (lines.size() < 2)  // not writing to file, maybe open in and out separately
    {
        if (!is_on)
        {
            temp_line = "n";
        }
        else if (is_on)
        {
            temp_line = "y";
        }

        lines.push_back(temp_line);
        for (std::string &line : lines)
        {
            file << line << std::endl;
        }
    }
    else
    {
        if (!is_on)
        {
            lines[1] = "n";
        }
        else if (is_on)
        {
            lines[1] = "y";
        }

        for (std::string &line : lines)
        {
            file << line << std::endl;
        }
    }

    file.close();
    return true;
}

