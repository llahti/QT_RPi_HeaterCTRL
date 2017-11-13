#ifndef CONTROLLER_INTERFACE_H
#define CONTROLLER_INTERFACE_H

#include <QObject>
#include "measurement_package.h"

/**
 * @brief The ControllerPlugin class
 * This is a base class for boiler controller plugins
 */
class ControllerPlugin : public QObject
{
  Q_OBJECT

public:
  ControllerPlugin(QObject* parent = Q_NULLPTR) : QObject(parent) {}

public slots:
  // Receives measurement and runs one control cycle
  virtual void ProcessMeasurement(MeasurementPackage measpack);
  // Should read latest settings and apply those into controller
  virtual void RefreshSettings();

};

#endif // CONTROLLER_INTERFACE_H
