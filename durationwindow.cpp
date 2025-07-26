#include "durationwindow.hh"
#include <QString>



DurationWindow::DurationWindow():
    widgetCentral_(new QWidget(this)),
    gLayout_(new QGridLayout(widgetCentral_))
{
    infotext_ = new QLabel("Waddup bitch");
    gLayout_->addWidget(infotext_, 3, 3);

    newtime_box_ = new QSpinBox(this);
    gLayout_->addWidget(newtime_box_, 4, 3);
}

DurationWindow::~DurationWindow()
{}
