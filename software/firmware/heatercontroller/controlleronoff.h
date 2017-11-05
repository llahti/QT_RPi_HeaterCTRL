#ifndef CONTROLLERONOFF_H
#define CONTROLLERONOFF_H

#include "../heaterdata/heaterdata.h"
#include <QThread>
#include "controllerplugin.h"

/**
 * @brief The ControllerONOFF class
 * Simple on/off controller
 */
class ControllerONOFF : public ControllerPlugin
{
public:
  ControllerONOFF();
  ControllerONOFF(HeaterData* pHeaterdata) : ControllerPlugin(pHeaterdata) {}
  void run() override;

private:

};

#endif // CONTROLLERONOFF_H
