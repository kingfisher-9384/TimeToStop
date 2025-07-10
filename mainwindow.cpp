#include "mainwindow.hh"
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    widgetCentral_(new QWidget(this)),
    gLayout_(new QGridLayout(widgetCentral_)),
    hour_label_(new QLabel("01")),
    minute_label_(new QLabel("00")),
    second_label_(new QLabel("00")),
    hours_(1),
    minutes_(0),
    seconds_(0),
    isTimerOn_(true)

{
    setCentralWidget(widgetCentral_);

    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(timerFunction()));

    init_buttons();
    init_labels();
}



MainWindow::~MainWindow()
{}

void MainWindow::init_buttons()
{
    onOffButton_ = new QPushButton("ON/OFF", this);
    somethingButton_ = new QPushButton("Something", this);
    changeDurationButton_ = new QPushButton("Change duration", this);

    gLayout_->addWidget(onOffButton_, 5, 1);
    gLayout_->addWidget(somethingButton_, 5, 3);
    gLayout_->addWidget(changeDurationButton_, 5, 5);

    gLayout_->addItem(new QSpacerItem(100, 1), 5, 2);
    gLayout_->addItem(new QSpacerItem(100, 1), 5, 4);
}


void MainWindow::init_labels()
{
    gLayout_->addWidget(hour_label_, 3, 2);
    gLayout_->addWidget(minute_label_, 3, 3);
    gLayout_->addWidget(second_label_, 3, 4);

    second_label_->setFixedWidth(100); // center this shit somehow
}


void MainWindow::timer_func()
{
    if (seconds_ == 0 && minutes_ == 0 && hours_ == 0)
    {
        //timer_end();
    }

    --seconds_;

    if (seconds_ == 0 && minutes_ > 0)
    {
        --minutes_;
        seconds_ = 60;
    }

    if (minutes_ == 0 && hours_ > 0)
    {
        --hours_;
        minutes_ = 60;
    }

    if (hours_ == 0)
    {
        minutes_ = 60;
    }

    hour_label_->setText(QString::number(hours_));
    minute_label_->setText(QString::number(minutes_));
    second_label_->setText(QString::number(seconds_));
}


