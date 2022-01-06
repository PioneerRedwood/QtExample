#include <QGridLayout>
#include <QSignalMapper>

#include "custom_event.h"
#include "main_window.h"
#include "./ui_main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    cw = std::make_unique<CustomWidget>(this);

    cw = new CustomWidget(ui->centralwidget);
    this->layout()->addWidget(cw);
//    ui->gridLayout->addWidget(cw, 2, 2, 1, 1);
//    ui->gridLayout->addWidget(cw);
    cw->resize(100, 200);

    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete cw;
}


void MainWindow::initialize() {
//    adjustSize();
    // basic window settings
    setWindowTitle(tr("QtProject01"));

    connect(ui->changeMainWidgetColorBtn, &QPushButton::clicked, this,
            [this](){

        ui->mainWidget->setStyleSheet("background-color: red");

        qDebug() << "MainWidget: " << ui->mainWidget->pos() << "CustomWidget: " << cw->pos();
    });

    // pushButton click event

    // QSignalMapper
    // std::unique_ptr<QSignalMapper> signalMapper = std::make_unique<QSignalMapper>(this);
    // signalMapper->setMapping(ui->pushButton, )

    // lambda
    connect(ui->changeCustomWidgetColorBtn, &QPushButton::clicked, this,
            [this](){
       cw->changeColor();
    });
//    QObject::connect(ui->pushButton, &QPushButton::clicked, [this](){
//        this->cw->changeColor();
//    });


}



