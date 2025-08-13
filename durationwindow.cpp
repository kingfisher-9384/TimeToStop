#include "durationwindow.hh"
#include "saveservice.hh"
#include <QString>



DurationWindow::DurationWindow(QWidget* parent):
    QWidget(parent, Qt::Window),
    widgetCentral_(new QWidget(this)),
    gLayout_(new QGridLayout(widgetCentral_))
{
    infotext_ = new QLabel("Waddup bitch", this);  // init to variable previous time from mainwindow
    gLayout_->addWidget(infotext_, 1, 3);
    infotext_->setStyleSheet("font: 30pt;");

    hourBox_ = new QSpinBox(this);
    gLayout_->addWidget(hourBox_, 3, 3);
    hourBox_->setMinimum(0);
    hourBox_->setMaximum(23);     // MAYBE CHANGE THESE TO LIKE MAX 10HRS change it also in slot func

    minuteBox_ = new QSpinBox(this);
    gLayout_->addWidget(minuteBox_, 3, 4);
    minuteBox_->setMinimum(0);
    minuteBox_->setMaximum(59);

    saveButton_ = new QPushButton("Save", this);
    gLayout_->addWidget(saveButton_, 5, 3);

    gLayout_->addItem(new QSpacerItem(100, 1), 5, 1);
    gLayout_->addItem(new QSpacerItem(100, 1), 5, 2);
    gLayout_->addItem(new QSpacerItem(100, 1), 5, 5);
    gLayout_->addItem(new QSpacerItem(100, 1), 5, 6);

    this->setMinimumSize(700, 150);
    this->adjustSize();
    //this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //this->setMinimumSize(0, 0);

    // at which location in the mainwindow is the windowe created maybe the mainwindow limits it

    connect(saveButton_, &QPushButton::clicked, this, &DurationWindow::save_change_slot);
    connect(hourBox_, &QSpinBox::valueChanged, this, &DurationWindow::update_time_label);
    connect(minuteBox_, &QSpinBox::valueChanged, this, &DurationWindow::update_time_label);
}

DurationWindow::~DurationWindow()
{}


void DurationWindow::save_change()
{
    new_hours_ = hourBox_->value();
    new_minutes_ = minuteBox_->value();

    SaveService::saveTime();
}

bool DurationWindow::save_change_slot()
{
    if (hourBox_->value() == 0 && minuteBox_->value() == 0)
    {
        infotext_->setText("Error: Time can't be 0.");
        qDebug() << "error: tried to set time to 0";
        qDebug() << "hour:  " << new_hours_;
        qDebug() << "minute:  " << new_minutes_;
        return false;
    }

    if (hourBox_->value() > 23)
    {
        return false;
    }
    if (hourBox_->value() < 0)
    {
        return false;
    }

    if (minuteBox_->value() > 59)
    {
        return false;
    }
    if (hourBox_->value() < 0)
    {
        return false;
    }

    save_change();

    qDebug() << "new time successfully set";
    qDebug() << "hour:  " << new_hours_;
    qDebug() << "minute:  " << new_minutes_;
    return true;
}

void DurationWindow::update_time_label()
{
    QString hourz = QString::number(hourBox_->value());
    QString minutez = QString::number(minuteBox_->value());
    if (hourBox_->value() < 10)
        hourz = "0" + hourz;
    if (minuteBox_->value() < 10)
        minutez = "0" + minutez;

    infotext_->setText(hourz + ":" + minutez);
}
