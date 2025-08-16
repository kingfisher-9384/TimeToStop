#ifndef SAVESERVICE_HH
#define SAVESERVICE_HH
#include <fstream>
#include <QString>
#include <QDir>


class SaveService
{
public:
    SaveService();

    bool static saveTime(int hours, int minutes);
    bool static readTime();

    private:
    std::fstream file_;

    // this class is only for creating and modifying the json file not for any other logic
    // maybe add some sort of encryption so that not just plaintext
};

#endif // SAVESERVICE_HH
