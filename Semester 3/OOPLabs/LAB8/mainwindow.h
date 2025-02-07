#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include "TFSin.h"
#include "TFSi.h"

class GraphWidget : public QWidget {
    Q_OBJECT

private:
    unsigned int degree;
    double minX, maxX;

public:
    explicit GraphWidget(QWidget *parent = nullptr);
    void setParams(double minX, double maxX);

protected:
    void paintEvent(QPaintEvent *event) override;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onUpdateGraph();

private:
    GraphWidget *graphWidget;
    QSpinBox *minXSpinBox;
    QSpinBox *maxXSpinBox;
    QPushButton *updateButton;
};

#endif // MAINWINDOW_H
