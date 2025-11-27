#ifndef SAVESERVICE_HH
#define SAVESERVICE_HH
#include <utility>
#include <QDir>
#include <vector>
#include <string>


class SaveService
{
public:
    SaveService();

    bool static save_time(const int& hours, const int& minutes);
    bool static set_onoff(bool is_on);
    std::pair<int,int> static read_time();
    bool static read_onoff();
    std::pair<int,int> static get_current_time();


    private:
    std::pair<int,int> static get_time_from_line(std::vector<std::string>& lines);
    std::vector<std::string> static get_file_contents();
    void static write_to_file(std::vector<std::string>& lines);

    /// \brief checks if the file contents are correct
    /// \return
    /// 0 if empty
    /// if 1 line: valid number 11, y/n 12, else 10
    /// if 2 lines: 1st line valid number + 2nd line y/n 21, else 20
    /// else 30
    int static check_file_state();
    void static set_default_file_state();

    // this class is only for creating and modifying the json file not for any other logic
    // maybe add some sort of encryption so that not just plaintext
    // bro start using pointers this shit is mad unoptimized
};

#endif // SAVESERVICE_HH
