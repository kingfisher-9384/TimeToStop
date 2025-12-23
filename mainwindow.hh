#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QWidget>
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QCloseEvent>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:

    void timer_on_off();

    void change_duration();

    void timer_func();

    void something_func();

private:

    QWidget* widgetCentral_;
    QGridLayout* gLayout_;

    QPushButton* onOffButton_;
    QPushButton* somethingButton_;
    QPushButton* changeDurationButton_;

    QLabel* timeLabel_;

    QTimer* timer_;


    const int INTERVAL = 1000;
    int hours_;
    int minutes_;
    int seconds_;

    bool is_timer_on_;                               // optimize this whole codebase this shit is atrocious

    bool is_first_run_;

    QString hourz = QString::number(hours_);
    QString minutez = QString::number(minutes_);        // wtf is this??
    QString secondz = QString::number(seconds_);        // is this even usable?

    void init_buttons();

    void init_labels();   // title label, remaining label, end label

    void update_labels();

    void update_time_label();

    void read_from_saves();  // error checks

    void timer_end();

    void system_command(char command);

    bool add_to_startup();

    bool remove_from_startup();
};
#endif // MAINWINDOW_HH
