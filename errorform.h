#ifndef ERRORFORM_H
#define ERRORFORM_H

#include <QDialog>

namespace Ui {
class ErrorForm;
}

class ErrorForm : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorForm(QWidget *parent = nullptr);
    ~ErrorForm();

private:
    Ui::ErrorForm *ui;
private slots:
    void Ignor();


};

#endif // ERRORFORM_H
