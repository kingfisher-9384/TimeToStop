#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QWidget>
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include "durationwindow.hh"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    int timer_on_off();

    void change_duration();

    void timer_func();

    void something_func();

private:

    QWidget* widgetCentral_;
    QGridLayout* gLayout_;

    QPushButton* onOffButton_;
    QPushButton* somethingButton_;
    QPushButton* changeDurationButton_;

    QLabel* time_label_;

    QTimer* timer_;


    const int INTERVAL = 1000;
    int hours_;
    int minutes_;
    int seconds_;

    std::string previousTime_;
    bool read_prev_time();   // read the text to hours mins and secs

    bool isTimerOn_;   // maybe save the last state in a txt file or something cuz otherwise always init to on
                       // put logic into own class, like all the exe shit and background and save to txt
                       // check if file exists if not init to 1hr

    QString hourz = QString::number(hours_);
    QString minutez = QString::number(minutes_);
    QString secondz = QString::number(seconds_);

    //DurationWindow* window_;  // just in case i need to revert back

    void init_buttons();

    void init_labels();   // title label, remaining label, end label

    void update_labels();

    void update_time_label();

    int read_time();  // error checks

    void timer_end();

};
#endif // MAINWINDOW_HH
