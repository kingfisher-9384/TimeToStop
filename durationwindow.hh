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
    //void save_change_slot();  // error checks here but just call save_change


private:
    QWidget* widgetCentral_;
    QGridLayout* gLayout_;

    QSpinBox* hour_box_;
    QSpinBox* minute_box_;
    QLabel* infotext_;
    QPushButton* save_button_;

    int hours_ = 0;
    int minutes_ = 0;

    void save_change();

};

#endif // DURATIONWINDOW_HH
