#include "durationwindow.hh"
#include <QString>



DurationWindow::DurationWindow(QWidget* parent):
    QWidget(parent, Qt::Window),
    widgetCentral_(new QWidget(this)),
    gLayout_(new QGridLayout(widgetCentral_))
{
    infotext_ = new QLabel("Waddup bitch", this);
    gLayout_->addWidget(infotext_, 3, 3);
    infotext_->setStyleSheet("font: 30pt;");

    newtime_box_ = new QSpinBox(this);
    gLayout_->addWidget(newtime_box_, 4, 3);

    //this->setMinimumSize(300, 200);
    this->adjustSize();
    this->setMinimumSize(0, 0);
}

DurationWindow::~DurationWindow()
{}
