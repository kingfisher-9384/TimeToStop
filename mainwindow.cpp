#include "mainwindow.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    widgetCentral_(new QWidget(this)),
    outerBoxLayout_(new QBoxLayout(QBoxLayout::TopToBottom, widgetCentral_)),
    innerBoxLayout_(new QBoxLayout(QBoxLayout::LeftToRight, widgetCentral_)),
    duration_(3600000), // one hour
    isTimerOn_(true)

{
    setCentralWidget(widgetCentral_);

    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(timerFunction()));

    init_buttons();
    init_labels();

    timerFunction();
}



MainWindow::~MainWindow()
{}


