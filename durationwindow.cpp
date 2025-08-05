#include "durationwindow.hh"
#include <QString>



DurationWindow::DurationWindow(QWidget* parent):
    QWidget(parent, Qt::Window),
    widgetCentral_(new QWidget(this)),
    gLayout_(new QGridLayout(widgetCentral_))
{
    infotext_ = new QLabel("Waddup bitch", this);
    gLayout_->addWidget(infotext_, 1, 3);
    infotext_->setStyleSheet("font: 30pt;");

    hour_box_ = new QSpinBox(this);
    gLayout_->addWidget(hour_box_, 3, 2);
    hour_box_->setMinimum(0);
    hour_box_->setMaximum(23);     // MAYBE CHANGE THESE TO LIKE MAX 10HRS

    minute_box_ = new QSpinBox(this);
    gLayout_->addWidget(minute_box_, 3, 4);
    minute_box_->setMinimum(0);
    minute_box_->setMaximum(59);

    save_button_ = new QPushButton("Save", this);
    gLayout_->addWidget(save_button_, 5, 3);

    gLayout_->addItem(new QSpacerItem(100, 1), 5, 1);
    gLayout_->addItem(new QSpacerItem(100, 1), 5, 2);
    gLayout_->addItem(new QSpacerItem(100, 1), 5, 4);
    gLayout_->addItem(new QSpacerItem(100, 1), 5, 5);

    this->setMinimumSize(300, 150);
    this->adjustSize();
    //this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //this->setMinimumSize(0, 0);

    // at which location in the mainwindow is the windowe created maybe the mainwindow limits it

    connect(save_button_, &QPushButton::clicked, this, &DurationWindow::save_change);  // connect this to the slot function
}

DurationWindow::~DurationWindow()
{}


void DurationWindow::save_change()
{
    hours_ = hour_box_->value();
    minutes_ = minute_box_->value();

    qDebug() << "hour  " << hours_;
    qDebug() << "minute  " << minutes_;
}

