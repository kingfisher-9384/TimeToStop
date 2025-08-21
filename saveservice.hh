#ifndef SAVESERVICE_HH
#define SAVESERVICE_HH
#include <utility>
#include <QDir>


class SaveService
{
public:
    SaveService();

    bool static save_time(int hours, int minutes);
    std::pair<int,int> static read_time();
    bool static read_onoff();  // next up: this fucker


    private:
    std::pair<int,int> static get_time_from_line(std::vector<std::string>);
    bool static file_exists();


        const static int DEFAULT_HOUR = 1;
        const static int DEFAULT_MINUTE = 0;


    //const static std::string& path_;  try turning this shit into a variable

    // this class is only for creating and modifying the json file not for any other logic
    // maybe add some sort of encryption so that not just plaintext
};

#endif // SAVESERVICE_HH
