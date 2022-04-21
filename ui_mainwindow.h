/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnDisconnect;
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableWidget *tblAcp;
    QWidget *tab_2;
    QPlainTextEdit *consol;
    QWidget *tab_3;
    QPushButton *btnNomer;
    QTableWidget *tblNomer;
    QTableWidget *tblBSWV;
    QLabel *label;
    QLabel *greenMK3o;
    QLabel *redMK2r;
    QLabel *greenMK1r;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_2;
    QLabel *redMK3o;
    QLabel *redMK2o;
    QCheckBox *checkBox;
    QLabel *greenMK2r;
    QLabel *label_3;
    QLabel *redMK3r;
    QLabel *greenMK3r;
    QLabel *redMK1r;
    QLabel *greenMK1o;
    QLabel *label_5;
    QLabel *redMK1o;
    QLabel *greenMK2o;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1256, 725);
        MainWindow->setMinimumSize(QSize(1256, 725));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btnDisconnect = new QPushButton(centralwidget);
        btnDisconnect->setObjectName(QString::fromUtf8("btnDisconnect"));
        btnDisconnect->setGeometry(QRect(310, 10, 75, 23));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(400, 10, 75, 23));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(300, 300, 861, 361));
        tabWidget->setMinimumSize(QSize(861, 361));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tblAcp = new QTableWidget(tab);
        if (tblAcp->columnCount() < 3)
            tblAcp->setColumnCount(3);
        if (tblAcp->rowCount() < 7)
            tblAcp->setRowCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblAcp->setItem(0, 0, __qtablewidgetitem);
        tblAcp->setObjectName(QString::fromUtf8("tblAcp"));
        tblAcp->setEnabled(true);
        tblAcp->setGeometry(QRect(10, 20, 827, 281));
        tblAcp->setMinimumSize(QSize(827, 271));
        tblAcp->setRowCount(7);
        tblAcp->setColumnCount(3);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        consol = new QPlainTextEdit(tab_2);
        consol->setObjectName(QString::fromUtf8("consol"));
        consol->setGeometry(QRect(10, 10, 811, 301));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        btnNomer = new QPushButton(tab_3);
        btnNomer->setObjectName(QString::fromUtf8("btnNomer"));
        btnNomer->setGeometry(QRect(140, 160, 131, 23));
        tblNomer = new QTableWidget(tab_3);
        if (tblNomer->columnCount() < 3)
            tblNomer->setColumnCount(3);
        if (tblNomer->rowCount() < 2)
            tblNomer->setRowCount(2);
        tblNomer->setObjectName(QString::fromUtf8("tblNomer"));
        tblNomer->setGeometry(QRect(40, 30, 391, 111));
        tblNomer->setMinimumSize(QSize(391, 111));
        tblNomer->setRowCount(2);
        tblNomer->setColumnCount(3);
        tabWidget->addTab(tab_3, QString());
        tblBSWV = new QTableWidget(centralwidget);
        if (tblBSWV->columnCount() < 3)
            tblBSWV->setColumnCount(3);
        if (tblBSWV->rowCount() < 6)
            tblBSWV->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblBSWV->setItem(0, 0, __qtablewidgetitem1);
        tblBSWV->setObjectName(QString::fromUtf8("tblBSWV"));
        tblBSWV->setGeometry(QRect(300, 40, 861, 251));
        tblBSWV->setMinimumSize(QSize(861, 251));
        tblBSWV->setRowCount(6);
        tblBSWV->setColumnCount(3);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 60, 221, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(14);
        label->setFont(font);
        greenMK3o = new QLabel(centralwidget);
        greenMK3o->setObjectName(QString::fromUtf8("greenMK3o"));
        greenMK3o->setGeometry(QRect(200, 120, 61, 41));
        redMK2r = new QLabel(centralwidget);
        redMK2r->setObjectName(QString::fromUtf8("redMK2r"));
        redMK2r->setGeometry(QRect(140, 170, 61, 41));
        greenMK1r = new QLabel(centralwidget);
        greenMK1r->setObjectName(QString::fromUtf8("greenMK1r"));
        greenMK1r->setGeometry(QRect(80, 170, 61, 41));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(210, 100, 41, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        label_4->setFont(font1);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 180, 61, 21));
        label_6->setFont(font1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 100, 41, 21));
        label_2->setFont(font1);
        redMK3o = new QLabel(centralwidget);
        redMK3o->setObjectName(QString::fromUtf8("redMK3o"));
        redMK3o->setGeometry(QRect(200, 120, 61, 41));
        redMK2o = new QLabel(centralwidget);
        redMK2o->setObjectName(QString::fromUtf8("redMK2o"));
        redMK2o->setGeometry(QRect(140, 120, 61, 41));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(50, 240, 91, 21));
        greenMK2r = new QLabel(centralwidget);
        greenMK2r->setObjectName(QString::fromUtf8("greenMK2r"));
        greenMK2r->setGeometry(QRect(140, 170, 61, 41));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(150, 100, 41, 21));
        label_3->setFont(font1);
        redMK3r = new QLabel(centralwidget);
        redMK3r->setObjectName(QString::fromUtf8("redMK3r"));
        redMK3r->setGeometry(QRect(200, 170, 61, 41));
        greenMK3r = new QLabel(centralwidget);
        greenMK3r->setObjectName(QString::fromUtf8("greenMK3r"));
        greenMK3r->setGeometry(QRect(200, 170, 61, 41));
        redMK1r = new QLabel(centralwidget);
        redMK1r->setObjectName(QString::fromUtf8("redMK1r"));
        redMK1r->setGeometry(QRect(80, 170, 61, 41));
        greenMK1o = new QLabel(centralwidget);
        greenMK1o->setObjectName(QString::fromUtf8("greenMK1o"));
        greenMK1o->setGeometry(QRect(80, 120, 61, 41));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 130, 51, 21));
        label_5->setFont(font1);
        redMK1o = new QLabel(centralwidget);
        redMK1o->setObjectName(QString::fromUtf8("redMK1o"));
        redMK1o->setGeometry(QRect(80, 120, 51, 41));
        greenMK2o = new QLabel(centralwidget);
        greenMK2o->setObjectName(QString::fromUtf8("greenMK2o"));
        greenMK2o->setGeometry(QRect(140, 120, 61, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1256, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\232\320\237\320\220 \320\221\320\241\320\250-\320\222", nullptr));
        btnDisconnect->setText(QApplication::translate("MainWindow", "DisConnect", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Connect all", nullptr));

        const bool __sortingEnabled = tblAcp->isSortingEnabled();
        tblAcp->setSortingEnabled(false);
        tblAcp->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\320\224\320\260\320\275\320\275\321\213\320\265 \320\220\320\246\320\237 \320\264\320\273\321\217 \320\272\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\272\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\320\232\320\276\320\275\321\202\321\200\320\276\320\273\321\214", nullptr));
        btnNomer->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\265\321\200\320\270\321\202\321\214 \320\272\320\260\320\275\320\260\320\273\321\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\265\321\200\320\272\320\260 \320\274\320\276\320\275\321\202\320\260\320\266\320\260", nullptr));

        const bool __sortingEnabled1 = tblBSWV->isSortingEnabled();
        tblBSWV->setSortingEnabled(false);
        tblBSWV->setSortingEnabled(__sortingEnabled1);

        label->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \320\272\320\260\320\275\320\260\320\273\320\276\320\262", nullptr));
        greenMK3o->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        redMK2r->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        greenMK1r->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\320\234\320\2323", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\320\240\320\265\320\267\320\265\321\200\320\262\320\275\321\213\320\271", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\234\320\2321", nullptr));
        redMK3o->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        redMK2o->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "\320\225\321\201\321\202\321\214 \321\201\320\262\321\217\320\267\321\214", nullptr));
        greenMK2r->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\234\320\2322", nullptr));
        redMK3r->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        greenMK3r->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        redMK1r->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        greenMK1o->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\320\236\321\201\320\275\320\276\320\262\320\275\320\276\320\271", nullptr));
        redMK1o->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        greenMK2o->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
