#include "errorform.h"
#include "ui_errorform.h"

ErrorForm::ErrorForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorForm)
{
    ui->setupUi(this);
    connect(ui->btnIgnor,SIGNAL(clicked()),this,SLOT(Ignor));
}

ErrorForm::~ErrorForm()
{
    delete ui;
}

void ErrorForm::Ignor()
{
//ui->Hide();
}
