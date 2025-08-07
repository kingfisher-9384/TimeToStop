#ifndef DURATIONWINDOW_HH
#define DURATIONWINDOW_HH

#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>


class DurationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DurationWindow(QWidget *parent = 0);
    ~DurationWindow();

private slots:
    bool save_change_slot();


private:
    QWidget* widgetCentral_;
    QGridLayout* gLayout_;

    QSpinBox* hourBox_;
    QSpinBox* minuteBox_;
    QLabel* infotext_;
    QPushButton* saveButton_;

    int hours_ = 0;
    int minutes_ = 0;

    void save_change();
    void update_time_label();

};

#endif // DURATIONWINDOW_HH
