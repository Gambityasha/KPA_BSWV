#ifndef ERRORFORM_H
#define ERRORFORM_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class ErrorForm;
}

class ErrorForm : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorForm(QWidget *parent = nullptr);
    ~ErrorForm();
    QTimer *timerAnimation;
    QString errMsg = "Проблемы с подключенными устройствами.";
private:
    Ui::ErrorForm *ui;
private slots:

    void ReconnectAnimation();
    void AnimPlus1();
    void AnimPlus2();
    void on_btnIgnor_clicked();

signals:
void hideError();

};

#endif // ERRORFORM_H
