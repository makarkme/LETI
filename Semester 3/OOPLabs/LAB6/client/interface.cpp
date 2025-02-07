#include <QObject>
#include <QCoreApplication>
#include "interface.h"

int enum_n(0);

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
setWindowTitle("Работа №3");
    setFixedSize(400, 300);

    //name_n = new QLabel("Введите n: ", this);
    //name_n->setGeometry(30,20,80,25);

    //n = new QLineEdit("", this);
    //n->setGeometry(120,20,80,25);

    name_coefs = new QLabel("Введите корни/коэф-ы: ", this);
    name_coefs->setGeometry(30, 50, 175, 25);

    coefs = new QLineEdit("", this);
    coefs->setGeometry(215, 50, 100, 25);

    name_value = new QLabel("Введите значение: ", this);
    name_value->setGeometry(30, 82, 140, 25);

    value = new QLineEdit("", this);
    value->setGeometry(180, 82, 100, 25);

    print_canon_btn = new QPushButton("вывод по коэф-ам", this);
    print_canon_btn->setGeometry(30, 125, 150, 27);

    print_classic_btn = new QPushButton("вывод по корням", this);
    print_classic_btn->setGeometry(30, 165, 150, 27);

    calc_value_coefs_btn = new QPushButton("значение по коэф-ам", this);
    calc_value_coefs_btn->setGeometry(200, 125, 170, 27);

    calc_value_roots_btn = new QPushButton("значение по корням", this);
    calc_value_roots_btn->setGeometry(200, 165, 170, 27);

    output_value = new QLabel("тут будет значение",this);
    output_value->setGeometry(30, 250, 270, 27);

    output_polynom = new QLabel("тут будет полином",this);
    output_polynom->setGeometry(30, 215, 270, 27);

    i_mode = new QRadioButton("вещественные", this);
    i_mode->setGeometry(30, 20, 110, 25);

    c_mode = new QRadioButton("комплексные", this);
    c_mode->setGeometry(140, 20, 110, 25);

    connect(print_canon_btn,SIGNAL(pressed()),
            this,SLOT(formRequest()));
    connect(print_classic_btn,SIGNAL(pressed()),
            this,SLOT(formRequest()));
    connect(calc_value_coefs_btn,SIGNAL(pressed()),
            this,SLOT(formRequest()));
    connect(calc_value_roots_btn,SIGNAL(pressed()),
            this,SLOT(formRequest()));
}

TInterface::~TInterface()
{
    //delete name_n;
    //delete n;
    delete name_coefs;
    delete coefs;
    delete name_value;
    delete value;
    delete calc_value_coefs_btn;
    delete calc_value_roots_btn;
    delete print_canon_btn;
    delete print_classic_btn;
    delete output_value;
    delete output_polynom;
}

void TInterface::formRequest()
{
    QString s(" ");
    QStringList List = (coefs->text()).split(' ', QString::SkipEmptyParts);
    for(const auto& elem: List){
        s+=elem;
        s+= " ";
    }
    QString msg;
    if (i_mode->isChecked()){
        msg << QString().setNum(I_MODE);
    }
    else{
        msg << QString().setNum(C_MODE);
    }
    msg << s << value->text();
    QPushButton *btn = (QPushButton*)sender();
    if (btn == print_canon_btn){
        msg << QString().setNum(PRINT_CANON_REQUEST);
        enum_n = 2;
    }
    if (btn == print_classic_btn){
        msg << QString().setNum(PRINT_CLASSIC_REQUEST);
        enum_n = 1;
    }
    if (btn == calc_value_coefs_btn){
        msg << QString().setNum(CALC_VALUE_COEFS_REQUEST);
        enum_n = 3;
    }
    if (btn == calc_value_roots_btn){
        msg << QString().setNum(CALC_VALUE_ROOTS_REQUEST);
        enum_n = 4;
    }
    emit request(msg);
}

void TInterface::answer(QString msg)
{
    if(enum_n == 1 || enum_n == 2)
        output_polynom->setText(msg);
    else if(enum_n == 3 || enum_n == 4)
        output_value->setText(msg);
}
