#include "saveservice.hh"
#include <fstream>
#include <ctype.h>


const static int DEFAULT_HOUR = 1;
const static int DEFAULT_MINUTE = 0;
const static char DEFAULT_STATE = 'y';

int static CURRENT_HOUR = 0;
int static CURRENT_MINUTE = 0;


SaveService::SaveService()
{}


bool SaveService::save_time(const int& hours, const int& minutes)
{
    if (!QDir("data").exists())
    {
        QDir().mkdir("data");
    }

    std::vector<std::string> lines = get_file_contents();
    int file_state = check_file_state();

    std::string hourz = std::to_string(hours);    // could make this into separate global helper
    std::string minutez = std::to_string(minutes);
    if (hours < 10)
        hourz = "0" + hourz;
    if (minutes < 10)
        minutez = "0" + minutez;

    if (file_state == 0)
        lines.push_back(hourz + minutez);
    else if (file_state == 12)
        lines.emplace(lines.begin(), hourz + minutez);
    else
        lines[0] = hourz + minutez;

    write_to_file(lines);

    CURRENT_HOUR = hours;
    CURRENT_MINUTE = minutes;

    return true;
}


std::pair<int,int> SaveService::read_time()
{
    if (!std::filesystem::exists("data/saves.json"))   // error handling for when doesn't exist and crashes (just chuck some error)
    {
        save_time(DEFAULT_HOUR, DEFAULT_MINUTE);       // add exists checks everywhere where file is written to or read NO NEED
    }

    std::vector<std::string> lines = get_file_contents();
    std::pair<int,int> hour_and_min = get_time_from_line(lines);
    CURRENT_HOUR = hour_and_min.first;
    CURRENT_MINUTE = hour_and_min.second;
    return hour_and_min;
}


std::pair<int,int> SaveService::get_time_from_line(std::vector<std::string>& lines)
{
    std::string time = lines[0];
    auto temp_string = std::string(1, time[0]) + time[1];
    int hour = std::stoi(temp_string);
    temp_string = std::string(1, time[2]) + time[3];
    int minute = std::stoi(temp_string);

    return (std::pair<int,int>(hour, minute));
}


bool SaveService::set_onoff(bool is_on)             // maybe like add ui element for on off??
{
    std::string temp_line;
    std::vector<std::string> lines = get_file_contents();
    int file_state = check_file_state();

    if (file_state == 11 || file_state == 0)
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
    else if (file_state == 10 || file_state == 12)
    {
        if (!is_on)
        {
            lines[0] = "n";
        }
        else if (is_on)
        {
            lines[0] = "y";
        }

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
    else if (file_state == 12)
    {
        std::vector<std::string> lines = get_file_contents();
        if (lines[0] == "y")
        {
            return true;
        }
        else if (lines[0] == "n")
        {
            return false;
        }
    }
    else
    {
        set_default_file_state();
    }

    return true;
}

std::pair<int,int> SaveService::get_current_time()
{
    return (std::pair<int,int>(CURRENT_HOUR, CURRENT_MINUTE));
}


std::vector<std::string> SaveService::get_file_contents()
{
    if (!std::filesystem::exists("data/saves.json"))
    {
        set_default_file_state();
    }

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


void SaveService::write_to_file(std::vector<std::string>& lines)
{
    std::ofstream file("data/saves.json");
    for (std::string &line : lines)
    {
        file << line << std::endl;
    }
    file.close();
    return;
}


int SaveService::check_file_state()
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
            if (file_contents[1] == "n" || file_contents[1] == "y")
                second_line_check = true;
        }

        if (first_line_check && second_line_check)
            return 21;

        return 20;
    }

    else
        return 30;
}


void SaveService::set_default_file_state()
{
    std::ofstream file("data/saves.json");

    save_time(DEFAULT_HOUR, DEFAULT_MINUTE);
    set_onoff(DEFAULT_STATE);

    CURRENT_HOUR = DEFAULT_HOUR;
    CURRENT_MINUTE = DEFAULT_MINUTE;
}

