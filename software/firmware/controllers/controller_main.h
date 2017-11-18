#ifndef CONTROLLER_MAIN_H
#define CONTROLLER_MAIN_H

#include <QObject>

#include "controller_interface.h"

#include "controller_circulationpump.h"
#include "hal.h"

class Controller_Main : public Controller_Interface
{
public:
    Controller_Main(QObject* parent = Q_NULLPTR);

    // Sub controllers as public members for easier access
    Controller_CirculationPump circPump;

    // HAL instance
    HAL hal;

private:
};

#endif // CONTROLLER_MAIN_H
