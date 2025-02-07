#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include "communicator.h"
#include "common.h"

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

    QRadioButton *i_mode;
    QRadioButton *c_mode;
//    friend QString& operator<< (QString&,const QString&);

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

public slots:
    void answer(QString);

private slots:
    void formRequest();

signals:
    void request(QString);

/*public slots:
    void calc_value_coefs();
    void calc_value_roots();
    void print_canon();
    void print_classic();
};*/

};

#endif // INTERFACE_H
