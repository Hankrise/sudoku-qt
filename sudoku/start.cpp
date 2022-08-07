#include "start.h"
#include "ui_start.h"
#include "widget.h"
#include "QDialog"
#include <QGraphicsDropShadowEffect>

Start::Start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
    setWindowTitle("START");
    setWindowIcon(QIcon(":/image/s4.png"));
    this->initUI();

//以下为美化
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    ui->widget_3->setStyleSheet("background-color: rgb(255, 255, 255);"
                                 "border:2px solid rgb(20,196,188);border-radius:15px;");

    this->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(251,102,102, 200), stop:1 rgba(20,196,188, 210));");

    ui->label_image->setStyleSheet("border:2px solid rgb(20,196,188);border-radius:15px;");

    ui->label->setStyleSheet("border:none; background:transparent");

    ui->label_2->setStyleSheet("border:none; background:transparent");

    ui->widget->setStyleSheet("border:none; background:transparent");

    //ui->label_logo->setStyleSheet("border:none; background:transparent");

    //ui->label_image->setStyleSheet("border:none; background:transparent");



    ui->easyButton->setStyleSheet("QPushButton{background-color: rgb(20,196,188);"
                                    "border:2px solid rgb(20,196,188);border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->medium1Button->setStyleSheet("QPushButton{background-color: rgb(20,196,188);"
                                    "border:2px solid rgb(20,196,188);border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->hardButton->setStyleSheet("QPushButton{background-color: rgb(20,196,188);"
                                    "border:2px solid rgb(20,196,188);border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed


    ui->label_image->setStyleSheet("image: url(:/image/5180470.jpg);");

    ui->label_image->setStyleSheet("background: url(:/image/5180470.jpg);");

    ui->label_logo->setStyleSheet("image: url(:/image/clipart953982-1.png);");

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(-3, 0);
    shadow->setColor(QColor("#888888"));
    shadow->setBlurRadius(30);
    ui->label_image->setGraphicsEffect(shadow);




    //ui->label_logo->setStyleSheet("background: url(:/image/clipart953982-1.png);");

}

Start::~Start()
{
    delete ui;
}

void Start::initUI()
{
    QObject::connect(ui->easyButton,&QPushButton::clicked,this,[=](){
        Widget* wid = new Widget(nullptr,1);
        wid->show();
        this->hide();
    });
    QObject::connect(ui->medium1Button,&QPushButton::clicked,this,[=](){
        Widget* wid = new Widget(nullptr,2);
        wid->show();
        this->hide();
    });
    QObject::connect(ui->hardButton,&QPushButton::clicked,this,[=](){
        Widget* wid = new Widget(nullptr,3);
        wid->show();
        this->hide();
    });
}


