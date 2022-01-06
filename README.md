# QtExample
for studying by self about Qt

## Other opensource project
- QCefView (here qcview): https://github.com/tishion/QCefView -> qcview
- CefViewCore: https://github.com/CefView/CefViewCore ..

## cef-grogu to QtExample migration
- Qt_tutorial, qcview .. 

## Qt_tutorial
- actually, it is not a tutorial.. bad naming on project
### Qt connect sementic
```C++
// see Qt_tutorial/mainwindow.h
class MainWindow {
...
private slots:
void closeWindow();
void minimizeWindow();
...
}

// see Qt_tutorial/mainwindow.cpp
MainWindow::MainWindow {
    ...
    // MainWindow settings
    this->setWindowFlags(Qt::CustomizeWindowHint);
    this->setWindowFlags(Qt::FramelessWindowHint);

    // cotrolFrame's elements settings  
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
    connect(ui->minimizeButton, SIGNAL(clicked()), this, SLOT(minimizeWindow()));
    ...
}

```
- Signal and Slots in Qt
- make window different like `FramelessWindow`


## QtProject01
- inspired "just do it your project"
- my custom view not showing ..? why?

### signal, slot to lambda upper C++11
```C++
// see QtProject01/main_window.cpp
void MainWindow::initialize() {

    connect(ui->changeMainWidgetColorBtn, &QPushButton::clicked, this,
            [this](){
                ui->mainWidget->setStyleSheet("background-color: red");
                qDebug() << "MainWidget: " << ui->mainWidget->pos() << "CustomWidget: " << cw->pos();
            }
    );
}
```

### custom view dynamically allocate
```C++
class MainWindow {
private:
    CustomView* cw; // std::unique_ptr<CustomView> cw // can be worked well
}
...

MainWindow::MainWindow() {
    cw = new CustomWidget(ui->centralwidget); // look at the hierarchy of MainWindow
    ui->gridLayout->addWidget(cw, 2, 2, 1, 1);
}

```

# References
- [signal and slots in Qt](https://www.vikingsoftware.com/blog/getting-the-most-of-signal-slot-connections-in-qt/)
