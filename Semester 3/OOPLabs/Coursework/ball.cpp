#include "ball.h"

Ball::Ball(QWidget *parent) : QWidget(parent), ballX(300), ballY(400), angle(45), radius(25), speed(20), timer(0) {
    angle = qDegreesToRadians(angle); // Переводим угол в радианы

    // Вычисляем начальные скорости по X и Y
    velocityX = speed * qCos(angle);
    velocityY = speed * qSin(angle);
}

void Ball::paintEvent(QPaintEvent *event) {
    QPainter painter(this);                                                      // Инициализация функции для отрисовки
    painter.setBrush(Qt::white);                                                 // Цвет шарика
    painter.drawEllipse(ballX - radius, ballY - radius, 2 * radius, 2 * radius); // Рисуем шарик
}

void Ball::timerEvent(QTimerEvent *event) {
    // Обновляем позицию шарика
    ballX += velocityX;
    ballY += velocityY;

    if (ballX - radius <= 0 or ballX + radius >= width()) { // Столкновение с правой и левой стенками
        velocityX = -velocityX;  // Меняем направление по X
    }

    if (ballY - radius <= 0 or ballY + radius >= height()) { // Столкновение с верхней и нижней стенками
        velocityY = -velocityY;  // Меняем направление по Y
    }

    update(); // Перерисовываем экран
}

void Ball::startMotion() {
    timer = startTimer(13); // Таймер для обновления положения шарика положение шарика (значение в скобках влияет на плавность движения)
}

void Ball::initialState() {
    if (timer) {
        killTimer(timer);  // Останавливаем таймер
        timer = 0;

        ballX = 300; // возвращаем шарик в первоначальное положение
        ballY = 400;

        update(); // Перерисовываем экран
    }
}

void Ball::setSpeed(float newSpeed) {
    speed = newSpeed;
    velocityX = speed * qCos(angle);
    velocityY = speed * qSin(angle);
}

void Ball::setAngle(float newAngle) {
    angle = qDegreesToRadians(newAngle);
    velocityX = speed * qCos(angle);
    velocityY = speed * qSin(angle);
}

void Ball::setRadius(float newRadius) {
    radius = newRadius;
}

bool Ball::isMotionStopped() const {
    return timer == 0; // Вернёт  true если timerId = 0 (то есть, если шарик неподвижен)
}
