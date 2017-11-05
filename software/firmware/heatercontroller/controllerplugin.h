#ifndef CONTROLLERPLUGIN_H
#define CONTROLLERPLUGIN_H

#include "../heaterdata/heaterdata.h"
#include <QThread>

/**
 * @brief The ControllerPlugin class
 * This is a base class for boiler controllers
 */
class ControllerPlugin : public QThread
{
  Q_OBJECT
public:
  ControllerPlugin();
  ControllerPlugin(HeaterData* pHeaterdata);
  void run();



protected:
  HeaterData* heaterdata;
  bool stopThread; // Flag to stop thread
};

#endif // CONTROLLERPLUGIN_H
