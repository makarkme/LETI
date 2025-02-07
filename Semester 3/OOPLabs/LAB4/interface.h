#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "polynom.h"
#include "array.h"
#include "number.h"
#include <QVBoxLayout>

class TInterface : public QWidget
{
    Q_OBJECT

    QLabel *name_n;
    QLabel *name_coefs;
    QLabel *name_value;
    QLabel *output_value;
    QLabel *output_polynom;

    QLineEdit *n;
    QLineEdit *coefs;
    QLineEdit *value;


    QPushButton *calc_value_coefs_btn;
    QPushButton *calc_value_roots_btn;
    QPushButton *print_canon_btn;
    QPushButton *print_classic_btn;

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

public slots:
    void calc_value_coefs();
    void calc_value_roots();
    void print_canon();
    void print_classic();
};
#endif // INTERFACE_H
