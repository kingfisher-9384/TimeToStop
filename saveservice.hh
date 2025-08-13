#ifndef SAVESERVICE_HH
#define SAVESERVICE_HH
#include <fstream>
#include <QString>
#include <QDir>


class SaveService
{
public:
    SaveService();

    bool static saveTime();
    bool readTime();

    private:
    std::fstream file_;

    //QString path_ = "ProgramData/saves";

    // this class is only for creating and modifying the json file not for any other logic
    // maybe add some sort of encryption so that not just plaintext
};

#endif // SAVESERVICE_HH
