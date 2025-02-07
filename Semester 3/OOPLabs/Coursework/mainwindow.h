#pragma once

#include "ball.h"
#include "interface.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow { // наследуемся от QMainWindow
    private:
        Q_OBJECT // макрос от qt
        Ui::MainWindow *ui; // указатель на интерфейс
        Ball *ball; // Указатель на виджет с шариком

        void startBallMotion(); // запуск шарика
        void initialBallState(); // остановка шарика
        void setInputFieldsEnabled(bool enabled); // доступ к вводу в поля (например speedInput)
        void updateBallParameters(); // установка пользовательских данных о шарике

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

};
