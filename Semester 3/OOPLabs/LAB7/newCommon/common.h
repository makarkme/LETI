#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <type_traits>

enum messages
{
    PRINT_CLASSIC_REQUEST = 1,
    PRINT_CANON_REQUEST,
    CALC_VALUE_COEFS_REQUEST,
    CALC_VALUE_ROOTS_REQUEST,
    CALC_SIN,
    CALC_SI,
};

enum modes{
    I_MODE = 1,
    C_MODE,
    SIN_MODE,
};

extern const QChar separator;
QString& operator<< (QString&,const QString&);

#endif // COMMON_H
