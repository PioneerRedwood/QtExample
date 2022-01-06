#include "main_window.h"

#include <QApplication>
#include "custom_widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    CustomWidget cw;
//    cw.show();
    w.show();
    return a.exec();
}
