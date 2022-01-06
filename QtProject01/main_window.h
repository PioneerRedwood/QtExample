#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "custom_event.h"
#include "custom_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initialize();

private:
    Ui::MainWindow *ui;
//    std::unique_ptr<CustomWidget> cw;
    CustomWidget* cw;
};
#endif // MAINWINDOW_H
