#include <QDebug>
#include "custom_widget.h"

CustomWidget::CustomWidget(QWidget *parent)
    : QWidget{parent}
{
    this->initialize();
    setObjectName(QString::fromUtf8("CustomWidget"));
    setStyleSheet("background-color: green");
}

void CustomWidget::initialize() {
    qDebug() << "CustomWidget::initialize() " << window() << isVisible();


}

void CustomWidget::changeColor() {

    QString color = toggle_color_ ? "red" : "blue";
    qDebug() << "isVisible" << isVisible() << "color" << color;

    if(toggle_color_) {
        // turn to blue
        setStyleSheet("background-color: blue");
        toggle_color_ = false;
    } else {
        // turn to red
        setStyleSheet("background-color: red");
        toggle_color_ = true;
    }
}
