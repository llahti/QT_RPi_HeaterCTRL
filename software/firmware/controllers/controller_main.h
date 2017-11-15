#ifndef CONTROLLER_MAIN_H
#define CONTROLLER_MAIN_H

#include <QObject>

#include "controller_interface.h"

class Controller_Main : public Controller_Interface
{
public:
    Controller_Main(QObject* parent = Q_NULLPTR);
};

#endif // CONTROLLER_MAIN_H
