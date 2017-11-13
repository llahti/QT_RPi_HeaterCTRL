#ifndef CONTROLLER_BOILER_SIMPLE_H
#define CONTROLLER_BOILER_SIMPLE_H

#include <QThread>
#include "controller_interface.h"

// TODO: Begin to implement controller

/**
 * @brief The ControllerONOFF class
 * Simple on/off controller
 */
class ControllerONOFF : public ControllerPlugin
{
  Q_OBJECT

public:
  ControllerONOFF(QObject* parent = Q_NULLPTR);

private:

};

#endif // CONTROLLER_BOILER_SIMPLE_H
