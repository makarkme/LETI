#include "mainwindow.h"
#include <QPainter>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include "TFSin.h"
#include "TFSi.h"


GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent), degree(19), minX(-10), maxX(10){
    setFixedSize(800, 600);
}

void GraphWidget::setParams(double minX, double maxX) {
    this->minX = minX;
    this->maxX = maxX;
    update();
}

void GraphWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(QPen(Qt::black));
    painter.translate(width() / 2, height() / 2);
    painter.drawLine(-width() / 2, 0, width() / 2, 0);
    painter.drawLine(0, -height() / 2, 0, height() / 2);
    painter.setPen(QPen(Qt::red, 2));

    TFSin<double> sinFunc(degree);
    for (double x = minX; x <= maxX; x += 0.1) {
        double y = sinFunc(x);
        int screenX = static_cast<int>(x * 40);
        int screenY = static_cast<int>(-y * 40);
        painter.drawPoint(screenX, screenY);
    }

    painter.setPen(QPen(Qt::red));
    painter.setFont(QFont("Arial", 12));
    painter.drawText(-200, -60, "sin(x)");

    painter.setPen(QPen(Qt::blue, 2));

    TFSi<double> integralSinFunc(degree-6);

    for (double x = minX; x <= maxX; x += 0.1) {
        double y = integralSinFunc(x);
        int screenX = static_cast<int>(x * 40);
        int screenY = static_cast<int>(-y * 40);
        painter.drawPoint(screenX, screenY);
    }

    painter.setPen(QPen(Qt::blue));
    painter.drawText(90, -90, "Si(x)");
}




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    graphWidget = new GraphWidget(this);
    setCentralWidget(graphWidget);

    QVBoxLayout *layout = new QVBoxLayout();

    minXSpinBox = new QSpinBox(this);
    minXSpinBox->setRange(-100, 0);
    minXSpinBox->setValue(-10);

    maxXSpinBox = new QSpinBox(this);
    maxXSpinBox->setRange(0, 100);
    maxXSpinBox->setValue(10);

    updateButton = new QPushButton("Обновить график", this);

    layout->addWidget(minXSpinBox);
    layout->addWidget(maxXSpinBox);
    layout->addWidget(updateButton);

    QWidget *controlsWidget = new QWidget(this);
    controlsWidget->setLayout(layout);
    setMenuWidget(controlsWidget);

    connect(updateButton, &QPushButton::clicked, this, &MainWindow::onUpdateGraph);
}

MainWindow::~MainWindow() {
    delete graphWidget;
    delete minXSpinBox;
    delete maxXSpinBox;
    delete updateButton;
}

void MainWindow::onUpdateGraph() {
    double minX = minXSpinBox->value();
    double maxX = maxXSpinBox->value();
    graphWidget->setParams(minX, maxX);
}



