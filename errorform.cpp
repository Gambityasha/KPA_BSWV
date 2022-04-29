#include "errorform.h"
#include "ui_errorform.h"

ErrorForm::ErrorForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorForm)
{
    ui->setupUi(this);

    timerAnimation = new QTimer();
    timerAnimation->start(2000);
   // connect(this,SIGNAL(hideError()),this,SLOT(close()));
    connect(timerAnimation,SIGNAL(timeout()),this,SLOT(ReconnectAnimation()));
}

ErrorForm::~ErrorForm()
{
    delete ui;
}

void ErrorForm::ReconnectAnimation()
{
    ui->label->setText(errMsg);
    QTimer::singleShot(700,this,SLOT(AnimPlus1()));
    QTimer::singleShot(1200,this,SLOT(AnimPlus2()));
}

void ErrorForm::AnimPlus1()
{
    ui->label->setText(errMsg+".");
}

void ErrorForm::AnimPlus2()
{
    ui->label->setText(errMsg+"..");
}

void ErrorForm::on_btnIgnor_clicked()
{
    emit hideError();
    close();
}

