#include "interface.h"


using namespace ArrayClass;

TInterface::TInterface(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Работа №3");
    setFixedSize(400, 300);

    name_n = new QLabel("Введите n: ", this);
    name_n->setGeometry(30,20,80,25);

    n = new QLineEdit("", this);
    n->setGeometry(120,20,80,25);

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

    connect(print_canon_btn,SIGNAL(pressed()),this,SLOT(print_canon()));
    connect(print_classic_btn,SIGNAL(pressed()),this,SLOT(print_classic()));
    connect(calc_value_coefs_btn,SIGNAL(pressed()),this,SLOT(calc_value_coefs()));
    connect(calc_value_roots_btn,SIGNAL(pressed()),this,SLOT(calc_value_roots()));
}

TInterface::~TInterface()
{
    delete name_n;
    delete n;
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

void TInterface::calc_value_coefs(){
    Polynom polinom;
    Array arr;
    QStringList List = (coefs->text()).split(' ', QString::SkipEmptyParts);
    for(const auto& elem: List){
        arr.Append(elem.toDouble());
    }
    polinom.createPolynom(arr);
    polinom.setPrintMode(PrintModeCanonic);
    number val = polinom.countValue(value->text().toDouble());
    QString s("P(");
    s+=value->text();
    s+=") = ";
    s = s + QString::number(val, 'f', 2);
    output_value->setText(s);
}

void TInterface::calc_value_roots(){
    Polynom polinom;
    Array arr;
    QStringList List = (coefs->text()).split(' ', QString::SkipEmptyParts);
    for(const auto& elem: List){
        arr.Append(elem.toDouble());
    }
    polinom.createPolynom(arr);
    polinom.setPrintMode(PrintModeClassic);
    number val = polinom.countValue(value->text().toDouble());
    QString s("P(");
    s+=value->text();
    s+=") = ";
    s = s + QString::number(val, 'f', 2);
    output_value->setText(s);
}

void TInterface::print_canon(){
    Polynom polinom;
    Array arr;
    QStringList List = (coefs->text()).split(' ', QString::SkipEmptyParts);
    for(const auto& elem: List){
        arr.Append(elem.toDouble());
    }
    polinom.createPolynom(arr);
    polinom.setPrintMode(PrintModeCanonic);
    QString s("P(x) = ");
    for (int i = 0; i < arr.getLength(); i++) {
        if (i == arr.getLength() - 2) {
            s += QString::number(arr.getElement(i),'f',0);
            s += "x + ";
        }
        else if (i != arr.getLength() - 1) {
            s += QString::number(arr.getElement(i),'f',0);
            s += "x^";
            s += QString::number(arr.getLength() - 1 - i,'f',0);
            s += " + ";
        }
        else {
            s+= QString::number(arr.getElement(i),'f',0);
        }
    }
    output_polynom->setText(s);
}

void TInterface::print_classic(){
    Polynom polinom;
    Array arr;
    QStringList List = (coefs->text()).split(' ', QString::SkipEmptyParts);
    for(const auto& elem: List){
        arr.Append(elem.toDouble());
    }
    polinom.createPolynom(arr);
    polinom.setPrintMode(PrintModeClassic);
    QString s;
    s += "P(x) = ";
    s += QString::number(arr.getElement(0),'f',0);
    s += "(";
    for (int i = 1; i < arr.getLength(); i++) {
        if (i != arr.getLength() - 1) {
            s += "x - ";
            s += QString::number(arr.getElement(i),'f',0);
            s += ")(";
        }
        else {
            s += "x - ";
            s += QString::number(arr.getElement(i),'f',0);
            s += ")";
        }
    }
    output_polynom->setText(s);
}
