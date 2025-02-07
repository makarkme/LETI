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

void TApplication::recieve(QByteArray msg)
{
    int enum_n;
    Polynom polinom;
    Array arr;
    QString value, answer;
    QString msgString = QString(msg);
    int pos = msg.indexOf(separator);
    QString s = msgString.left(pos);
    QStringList List = (s).split(' ', QString::SkipEmptyParts);
    for(const auto& elem: List){
        arr.Append(elem.toDouble());
    }
    msgString.remove(0,pos+1);
    pos = msgString.indexOf(separator);
    value = msgString.left(pos);
    msgString.remove(0,pos+1);
    pos = msgString.indexOf(separator);
    enum_n = msgString.left(pos).toInt();
    polinom.createPolynom(arr);
    QString temp = "";
    number val;
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
            temp+=value;
            temp+=") = ";
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
    comm->send(QByteArray().append(answer));
}
