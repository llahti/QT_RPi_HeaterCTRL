#ifndef CONTROLLERONOFF_H
#define CONTROLLERONOFF_H

#include <QThread>
#include "controllerplugin.h"

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
  void run() override;

private:

};

#endif // CONTROLLERONOFF_H
