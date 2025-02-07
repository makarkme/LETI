#include "application.h"


using namespace ArrayClass;

TApplication::TApplication(int argc, char *argv[])
            : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                         QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(pars, this);

    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(recieve(QByteArray)));
}

long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

void TApplication::recieve(QByteArray msg)
{
    QString value, answer;
    QString msgString = QString(msg);
    int pos = msgString.indexOf(separator);
    int mode = msgString.left(pos).toInt();
    msgString.remove(0,2);
    pos = msgString.indexOf(separator);
    QString s = msgString.left(pos);
    QStringList List = (s).split(' ', QString::SkipEmptyParts);
    if (mode == 1 || mode == 2){
        if (mode == 1){
            Array<double> arr;
            Polynom<double> polinom;
            for(const auto& elem: List){
                arr.Append(elem.toDouble());
            }
            polinom.createPolynom(arr);
            msgString.remove(0,pos+1);
            pos = msgString.indexOf(separator);
            value = msgString.left(pos);
            msgString.remove(0,pos+1);
            pos = msgString.indexOf(separator);
            int enum_n = msgString.left(pos).toInt();
            QString temp = "";
            double val;
            switch (enum_n)
            {
            case PRINT_CLASSIC_REQUEST:
                polinom.setPrintMode(PrintModeClassic);
                temp += "P(x) = ";
                temp += QString::number(arr.getElement(0),'f',0);
                temp += "(";
                for (int i = 1; i < arr.getLength(); i++) {
                    if (i != arr.getLength() - 1) {
                        temp += "x - ";
                        temp += QString::number(arr.getElement(i),'f',0);
                        temp += ")(";
                    }
                    else {
                        temp += "x - ";
                        temp += QString::number(arr.getElement(i),'f',0);
                        temp += ")";
                    }
                }
                answer += temp;
                break;
            case PRINT_CANON_REQUEST:
                polinom.setPrintMode(PrintModeCanonic);
                temp = "P(x) = ";
                for (int i = 0; i < arr.getLength(); i++) {
                    if (i == arr.getLength() - 2) {
                        temp += QString::number(arr.getElement(i),'f',0);
                        temp += "x + ";
                    }
                    else if (i != arr.getLength() - 1) {
                        temp += QString::number(arr.getElement(i),'f',0);
                        temp += "x^";
                        temp += QString::number(arr.getLength() - 1 - i,'f',0);
                        temp += " + ";
                    }
                    else {
                        temp+= QString::number(arr.getElement(i),'f',0);
                    }
                }
                answer += temp;
                break;
            case CALC_VALUE_COEFS_REQUEST:
                polinom.setPrintMode(PrintModeCanonic);
                val = polinom.countValue(value.toDouble());
                temp = "P(";
                temp+= value;
                temp+= ") = ";
                temp = temp + QString::number(val, 'f', 2);
                answer += temp;
                break;
            case CALC_VALUE_ROOTS_REQUEST:
                polinom.setPrintMode(PrintModeClassic);
                val = polinom.countValue(value.toDouble());
                temp = "P(";
                temp += value;
                temp += ") = ";
                temp = temp + QString::number(val, 'f', 2);
                answer += temp;
                break;
            default: return;
            }
        }
        if (mode == 2){
            Array<Complex> arr;
            Polynom<Complex> polinom;
            double re = 0, im = 0, valueRe, valueIm;
            bool key = 0;
            for(const auto& elem: List){
                if (key == 0){
                    re = elem.toDouble();
                    key = 1;
                }
                else if (key == 1){
                    im = elem.toDouble();
                    key = 0;
                    Complex c(re, im);
                    arr.Append(c);
                }
            }
            polinom.createPolynom(arr);
            msgString.remove(0,pos+1);
            pos = msgString.indexOf(separator);
            value = msgString.left(pos);
            msgString.remove(0,pos+1);
            pos = msgString.indexOf(separator);
            int enum_n = msgString.left(pos).toInt();
            QString temp = "";
            Complex val;
            switch (enum_n)
            {
            case PRINT_CLASSIC_REQUEST:
                polinom.setPrintMode(PrintModeClassic);
                temp += "P(x) = ";
                temp += arr.getElement(0).toQString();
                if (arr.getLength() != 1){
                    temp += "(";
                    for (int i = 1; i < arr.getLength(); i++) {
                        if (i != arr.getLength() - 1) {
                            temp += "x - ";
                            temp += arr.getElement(i).toQString();
                            temp += ")(";
                        }
                        else {
                            temp += "x - ";
                            temp += arr.getElement(i).toQString();
                            temp += ")";
                        }
                    }
                }
                answer += temp;
                break;
            case PRINT_CANON_REQUEST:
                polinom.setPrintMode(PrintModeCanonic);
                temp = "P(x) = ";
                for (int i = 0; i < arr.getLength(); i++) {
                    if (i == arr.getLength() - 2) {
                        temp += arr.getElement(i).toQString();
                        temp += "x + ";
                    }
                    else if (i != arr.getLength() - 1) {
                        temp += arr.getElement(i).toQString();
                        temp += "x^";
                        temp += QString::number(arr.getLength() - 1 - i,'f',0);
                        temp += " + ";
                    }
                    else {
                        temp+= arr.getElement(i).toQString();
                    }
                }
                answer += temp;
                break;
            case CALC_VALUE_COEFS_REQUEST:
                polinom.setPrintMode(PrintModeCanonic);
                valueRe = (value.left(value.indexOf(" "))).toDouble();
                value.remove(0, value.indexOf(" ")+1);
                valueIm = value.toDouble();
                val = polinom.countValue(Complex(valueRe, valueIm));
                temp = "P";
                if (valueRe == 0 || valueIm == 0)
                    temp += "(";
                temp+=Complex(valueRe, valueIm).toQString();
                if (valueRe == 0 || valueIm == 0)
                    temp += ")";
                temp+=" = ";
                temp = temp + val.toQString();
                answer += temp;
                break;
            case CALC_VALUE_ROOTS_REQUEST:
                polinom.setPrintMode(PrintModeClassic);
                valueRe = (value.left(value.indexOf(" "))).toDouble();
                value.remove(0, value.indexOf(" ")+1);
                valueIm = value.toDouble();
                val = polinom.countValue(Complex(valueRe, valueIm));
                temp = "P";
                if (valueRe == 0 || valueIm == 0)
                    temp += "(";
                temp += Complex(valueRe, valueIm).toQString();
                if (valueRe == 0 || valueIm == 0)
                    temp += ")";
                temp += " = ";
                temp = temp + val.toQString();
                answer += temp;
                break;
            default:
                return;
            }
        }
    }
    if (mode == 3) {
        double re = msgString.left(msgString.indexOf(" ")).toDouble();
        msgString.remove(0, msgString.indexOf(" ") + 1);
        pos = msgString.indexOf(separator);
        double im = msgString.left(pos).toDouble();
        msgString.remove(0, pos+1);
        pos = msgString.indexOf(separator);
        int degree = msgString.left(pos).toInt();
        msgString.remove(0,pos+1);
        pos = msgString.indexOf(separator);
        int enum_n = msgString.left(pos).toInt();
        QString temp = "";
        Complex x(re,im);
        switch (enum_n) {
        case 5: {
            TFSin<Complex> sinFunction(degree);
            temp += "sin(" + x.toQString() + ") ≈ " + QString::number(sinFunction(x).getRe())
                    + " + " + QString::number(sinFunction(x).getIm()) + "i";
            answer += temp;
            break;
        }
        case 6: {
            TFSi<Complex> siFunction(degree);
            temp += "si(" + x.toQString() + ") ≈ " + QString::number(siFunction(x).getRe())
                    + " + " + QString::number(siFunction(x).getIm()) + "i";
            answer += temp;
            break;
        }
        default:
            return;
        }
    }
    comm->send(QByteArray().append(answer));
}
