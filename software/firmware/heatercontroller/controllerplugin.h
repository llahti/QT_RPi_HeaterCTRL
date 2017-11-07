#ifndef CONTROLLERPLUGIN_H
#define CONTROLLERPLUGIN_H

#include <QThread>

/**
 * @brief The ControllerPlugin class
 * This is a base class for boiler controllers
 */
class ControllerPlugin : public QThread
{
  Q_OBJECT

public:
  ControllerPlugin(QObject* parent = Q_NULLPTR);
  virtual void run();



protected:
  bool stopThread; // Flag to stop thread
};

#endif // CONTROLLERPLUGIN_H
