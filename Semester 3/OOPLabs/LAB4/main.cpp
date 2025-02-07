#include "interface.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font;
    font.setFamily("Trebuchet MS");
    font.setPointSize(12);
    a.setFont(font);
    TInterface w;
    w.show();
    return a.exec();
}
