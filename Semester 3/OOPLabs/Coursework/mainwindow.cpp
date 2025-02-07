#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this); // инициализируем интефейс

    ball = new Ball(ui->motionField); // Создаем и размещаем щарик внутри поля
    ball->setGeometry(0, 0, 600, 800);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startBallMotion); // Подключаем кнопку startButton к запуску шарика
    connect(ui->initialButton, &QPushButton::clicked, this, &MainWindow::initialBallState);

    ui->speedInput->setText("20"); // Устанавливаем начальные значения в поля ввода
    ui->angleInput->setText("45");
    ui->radiusInput->setText("25");

    setInputFieldsEnabled(true); // Поля ввода доступны при старте
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::startBallMotion() {
    if (ball->isMotionStopped()) {
        updateBallParameters(); // Устанавливаем начальные параметры при первом запуске
        ball->startMotion();
    }
    setInputFieldsEnabled(false); // Блокируем поля ввода
}

void MainWindow::setInputFieldsEnabled(bool enabled) {
    ui->speedInput->setEnabled(enabled);
    ui->angleInput->setEnabled(enabled);
    ui->radiusInput->setEnabled(enabled);
}

void MainWindow::initialBallState() {
    ball->initialState(); // Возвращаем шарик в начальное состояние
    setInputFieldsEnabled(true); // Разрешаем изменение параметров
}

void MainWindow::updateBallParameters() {
    float speed = ui->speedInput->text().toFloat(); // максмально можно ввести 5 цифр после запятой
    float angle = ui->angleInput->text().toFloat();
    float radius = ui->radiusInput->text().toFloat();


    if (speed > 0 and speed < 500) {
        ball->setSpeed(speed);
    }
    else {
        ball->setSpeed(20);
        ui->speedInput->setText("20");
    }

    if (angle >= 0 and angle <= 360) {
        ball->setAngle(angle);
    }
    else {
        ball->setAngle(45);
        ui->angleInput->setText("45");
    }
    if (radius > 0 and radius < 290) {
        ball->setRadius(radius);
    }
    else {
        ball->setRadius(25);
        ui->radiusInput->setText("25");
    }
}
