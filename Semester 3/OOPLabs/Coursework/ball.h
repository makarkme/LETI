#pragma once

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QtMath>
#include <QTimerEvent>

class Ball : public QWidget {
private:
    Q_OBJECT
    float ballX, ballY;         // Текущие координаты шарика
    float velocityX, velocityY; // Скорости по осям X и Y
    float angle;                // Угол направления движения
    float radius;               // Радиус шарика
    float speed;                // Скорость движения
    int timer;                  // переменная для управления таймером

protected:                                        // нужен для переопределения методов (переопределение - изменение родительского метода в дочернем классе)
    void paintEvent(QPaintEvent *event) override; // отрисовка шарика (переопределяем метод из библиотеки qt)
    void timerEvent(QTimerEvent *event) override; // отрисовка движения шарика (переопределяем метод из библиотеки qt)

public:
    explicit Ball(QWidget *parent = nullptr);
    ~Ball() = default;

    void startMotion();
    void initialState();

    void setSpeed(float newSpeed);
    void setAngle(float newAngle);
    void setRadius(float newRadius);

    bool isMotionStopped() const; // проверка на отсутствия движения шарика
};
