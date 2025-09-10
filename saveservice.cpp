#include "saveservice.hh"
#include <fstream>


SaveService::SaveService()
{}


bool SaveService::save_time(int hours, int minutes)
{

    if (!QDir("data").exists())
    {
        QDir().mkdir("data");
    }

    std::vector<std::string> lines = get_file_contents();

    std::string hourz = std::to_string(hours);    // MAYBE make this a separate func
    std::string minutez = std::to_string(minutes);
    if (hours < 10)
        hourz = "0" + hourz;
    if (minutes < 10)
        minutez = "0" + minutez;

    if (lines.size() < 1)
        lines.push_back(hourz + minutez);
    else if (lines[0] == "y" || lines[0] == "n")
        lines.emplace(lines.begin(), hourz + minutez);
    else
        lines[0] = hourz + minutez;

    std::fstream file;
    file.open("data/saves.json", std::ios::out);   // change this to ofstream

    for (unsigned int i = 0; i < lines.size(); ++i)
    {
        file << lines[i] << std::endl;
    }

    file.close();
    return true;
}


std::pair<int,int> SaveService::read_time()
{
    std::pair<int,int> hour_and_min;                   // make func that checks all lines to see if numbers or ny

    if (std::filesystem::exists("data/saves.json"))  // what if first line wrong then gives stoi error
    {
        std::vector<std::string> lines = get_file_contents();
        hour_and_min = get_time_from_line(lines);

        return hour_and_min;
    }
    else
    {
        save_time(DEFAULT_HOUR, DEFAULT_MINUTE);
        std::vector<std::string> lines = get_file_contents();
        hour_and_min = get_time_from_line(lines);

        return hour_and_min;
    }
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
    std::string temp_line;
    std::vector<std::string> lines = get_file_contents();

    if (lines.size() < 2)
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

        std::fstream file;
        file.open("data/saves.json", std::ios::out);   // make this a function too
        for (std::string &line : lines)
        {
            file << line << std::endl;
        }
        file.close();
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

        std::fstream file;
        file.open("data/saves.json", std::ios::out);
        for (std::string &line : lines)
        {
            file << line << std::endl;
        }
        file.close();
    }

    return true;
}

bool SaveService::read_onoff()
{
    // if 2nd line exists read, else set_onoff(true)
    // the internal onoff state doesn't correlate with the file value

    return true;
}


std::vector<std::string> SaveService::get_file_contents()
{
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
    file.close();
    return lines;
}

