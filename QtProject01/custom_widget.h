#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = nullptr);

    void initialize();

public slots:
    void changeColor();
    bool getColor() {return toggle_color_;}


private:

    //  red or blue
    bool toggle_color_ = false;

};

#endif // CUSTOMWIDGET_H
