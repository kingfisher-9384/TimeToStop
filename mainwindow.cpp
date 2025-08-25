#include "mainwindow.hh"
#include "durationwindow.hh"
#include "saveservice.hh"
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    widgetCentral_(new QWidget(this)),
    gLayout_(new QGridLayout(widgetCentral_)),
    hours_(0),
    minutes_(0),  // these prolly don't even need to bo initialized
    seconds_(0),
    is_timer_on_(true)

{
    setCentralWidget(widgetCentral_);

    read_from_saves();

    QString hourz = QString::number(hours_);
    QString minutez = QString::number(minutes_);
    QString secondz = QString::number(seconds_);
    if (hours_ < 10)
        hourz = "0" + hourz;
    if (minutes_ < 10)
        minutez = "0" + minutez;
    if (seconds_ < 10)
        secondz = "0" + secondz;

    timeLabel_= new QLabel(hourz + ":" + minutez + ":" + secondz);

    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(timer_func()));
    timer_->start(INTERVAL);

    init_buttons();
    init_labels();

    connect(onOffButton_, &QPushButton::clicked, this, &MainWindow::timer_on_off);
    connect(somethingButton_, &QPushButton::clicked, this, &MainWindow::something_func);
    connect(changeDurationButton_, &QPushButton::clicked, this, &MainWindow::change_duration);
}



MainWindow::~MainWindow()
{
}


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
    gLayout_->addWidget(timeLabel_, 3, 3);

    timeLabel_->setAlignment(Qt::AlignCenter);

    timeLabel_->setStyleSheet("font: 30pt;");
}


void MainWindow::timer_func()
{
    if (seconds_ == 0 && minutes_ == 0 && hours_ == 0)
    {
        //timer_end();
        timeLabel_->setText("GET FUCKED CUNT");
    }

    else
    {
        if (seconds_ == 0 && minutes_ == 0 && hours_ > 0)
        {
            --hours_;
            minutes_ = 60;
        }
        if (seconds_ == 0)
        {
            --minutes_;
            seconds_ = 60;
        }
        --seconds_;


        QString hourz = QString::number(hours_);
        QString minutez = QString::number(minutes_);
        QString secondz = QString::number(seconds_);

        if (hours_ < 10)
            hourz = "0" + hourz;
        if (minutes_ < 10)
            minutez = "0" + minutez;
        if (seconds_ < 10)
            secondz = "0" + secondz;

        timeLabel_->setText(hourz + ":" + minutez + ":" + secondz);
    }
}


void MainWindow::timer_on_off()
{
    if (is_timer_on_ == true)
    {
        is_timer_on_ = false;
        SaveService::set_onoff(false);
        qDebug() << "switched off";
        return;
    }

    if (is_timer_on_ == false)
    {
        is_timer_on_ = true;
        SaveService::set_onoff(true);
        qDebug() << "switched on";
        return;
    }

    qDebug() << "it's SOMEHOW shit itself";
    return;
}


void MainWindow::something_func()
{
    qDebug() << "something";
}


void MainWindow::change_duration()
{
    qDebug() << "changed duration";
    DurationWindow* window = new DurationWindow(this);
    window->show();
}


void MainWindow::read_from_saves()
{
    std::pair<int, int> hour_and_min = SaveService::read_time();

    hours_ = hour_and_min.first;
    minutes_ = hour_and_min.second;
}
