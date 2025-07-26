#ifndef DURATIONWINDOW_HH
#define DURATIONWINDOW_HH

#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>


// make this the child of mainwindow
class DurationWindow : public QWidget
{
    //Q_OBJECT
    // find out why this gives the vtable error

public:
    explicit DurationWindow();
    ~DurationWindow();

private slots:


private:
    QWidget* widgetCentral_;
    QGridLayout* gLayout_;

    QSpinBox* newtime_box_;
    QLabel* infotext_;




};

#endif // DURATIONWINDOW_HH
