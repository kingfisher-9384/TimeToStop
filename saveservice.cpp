#include "saveservice.hh"
#include <fstream>
#include <ctype.h>


SaveService::SaveService()
{}


bool SaveService::save_time(int hours, int minutes)
{

    if (!QDir("data").exists())
    {
        QDir().mkdir("data");
    }

    std::vector<std::string> lines = get_file_contents();

    std::string hourz = std::to_string(hours);    // could make this into separate global helper
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

    write_to_file(lines);
    return true;
}


std::pair<int,int> SaveService::read_time()
{
    std::pair<int,int> hour_and_min;                   // make func that checks all lines to see if numbers or ny (check file state)

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

        write_to_file(lines);
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

        write_to_file(lines);
    }

    return true;
}

bool SaveService::read_onoff()
{
    int file_state = check_file_state();
    if (file_state == 21)
    {
        std::vector<std::string> lines = get_file_contents();
        if (lines[1] == "y")
        {
            return true;
        }
        else if (lines[1] == "n")
        {
            return false;
        }
    }
    else if (file_state == 11)
    {
        set_onoff(DEFAULT_STATE);
    }
    else
    {
        fix_file(file_state);     // make func for if file is fucked aka its something other than 11 12 or 21
    }
    // ran outta time again, fuck my stupid chungus life

    // use check_file_state
    // if 2nd line exists read, else set_onoff(true)
    // the internal onoff state doesn't correlate with the file value

    return true;
}


std::vector<std::string> SaveService::get_file_contents()
{
    std::ifstream file("data/saves.json");

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


void SaveService::write_to_file(std::vector<std::string> lines)
{
    std::ofstream file("data/saves.json");
    for (std::string &line : lines)
    {
        file << line << std::endl;
    }
    file.close();
}


int SaveService::check_file_state()                                 // make other functions use this for checks
{
    std::vector<std::string> file_contents = get_file_contents();
    int contents_length = file_contents.size();

    if (contents_length < 1)
        return 0;

    else if (contents_length == 1)
    {
        int first_line_length = file_contents[0].length();

        if (first_line_length == 1)
        {
            if (file_contents[0] == "n" || file_contents[0] == "y")
                return 12;
        }

        if (first_line_length == 4)
        {
            if (std::all_of(file_contents[0].begin(), file_contents[0].end(), ::isdigit))
            {
                return 11;
            }
        }

        return 10;
    }

    else if (contents_length == 2)   // maybe checking if 4digit number is cvonvertable to time
    {
        bool first_line_check = false;
        bool second_line_check = false;

        int first_line_length = file_contents[0].length();
        if (first_line_length == 4)
        {
            if (std::all_of(file_contents[0].begin(), file_contents[0].end(), ::isdigit))
            {
                first_line_check = true;
            }
        }
        int second_line_length = file_contents[1].length();
        if (second_line_length == 1)
        {
            if (file_contents[0] == "n" || file_contents[0] == "y")
                second_line_check = true;
        }

        if (first_line_check && second_line_check)
            return 21;

        return 20;
    }

    else
        return 30;
}

