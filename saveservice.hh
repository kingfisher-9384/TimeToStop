#ifndef SAVESERVICE_HH
#define SAVESERVICE_HH
#include <string>
#include <QDir>


class SaveService
{
public:
    SaveService();

    bool static save_time(int hours, int minutes);
    std::string static read_time();
    bool static read_onoff();
    bool static file_exists();

    private:

    // this class is only for creating and modifying the json file not for any other logic
    // maybe add some sort of encryption so that not just plaintext
};

#endif // SAVESERVICE_HH
