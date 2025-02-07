#pragma once

#include <QVariant>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>


class Interface {
public:
    QWidget *centralwidget;
    QWidget *motionField;
    QWidget *menuField;
    QLabel *angleLabel;
    QPushButton *startButton;
    QLabel *speedLabel;
    QLabel *radiusLabel;
    QLineEdit *speedInput;
    QLineEdit *angleInput;
    QLineEdit *radiusInput;
    QPushButton *initialButton;
    QLabel *limitAngleLabel;
    QLabel *limitSpeedLabel;
    QLabel *limitRadiusLabel;

    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);
};

namespace Ui {
class MainWindow: public Interface {};
}
