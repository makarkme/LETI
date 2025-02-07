#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>

#include "common.h"
#include "communicator.h"
#include "array.h"
#include "polynom.h"
#include "TComplex.h"
#include "TFunction.h"
#include "TFSin.h"
#include "TFSi.h"

class TApplication : public QCoreApplication
{
    Q_OBJECT

    TCommunicator *comm;

public:

    TApplication(int, char**);

signals:

public slots:

    void recieve(QByteArray);

};

#endif // APPLICATION_H
