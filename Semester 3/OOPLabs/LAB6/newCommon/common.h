#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum messages
{
    PRINT_CLASSIC_REQUEST = 1,
    PRINT_CANON_REQUEST,
    CALC_VALUE_COEFS_REQUEST,
    CALC_VALUE_ROOTS_REQUEST,
};

enum modes{
    I_MODE = 1,
    C_MODE,
};

extern const QChar separator;
QString& operator<< (QString&,const QString&);

#endif // COMMON_H
