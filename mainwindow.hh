#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QWidget>
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>


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
    int remainingTime_;

    bool isTimerOn_;   // maybe save the last state in a txt file or something cuz otherwise always init to on
                       // put logic into own class, like all the exe shit and background and save to txt

    //int test_time = 0;

    QString hourz = QString::number(hours_);
    QString minutez = QString::number(minutes_);
    QString secondz = QString::number(seconds_);


    void init_buttons();

    void init_labels();   // title label, remaining label, end label

    void update_labels();

    void update_time_label();

    int read_time();  // error checks

    void timer_end();

};
#endif // MAINWINDOW_HH
