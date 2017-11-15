#ifndef CONTROLLER_INTERFACE_H
#define CONTROLLER_INTERFACE_H

#include <QObject>
#include "measurement_package.h"

/**
 * @brief The ControllerPlugin class
 * This is a base class for boiler controller plugins
 */
class Controller_Interface : public QObject
{
  Q_OBJECT

public:
  Controller_Interface(QObject* parent = Q_NULLPTR) : QObject(parent) {}

  // Initialze should be called as a first thing before starting controller
  // It ensures that all the settings are correctly installed and if not it'll do it
  // Also it handles all other initialization stuff needed for the controller
  virtual void Initialize() = 0;

public slots:
  // Receives measurement and runs one control cycle
  virtual void ProcessMeasurement(const MeasurementPackage measpack) = 0;

  // Should read latest settings and apply those into controller
  virtual void RefreshSettings() = 0;

  // Reset settings to factory defaults
  virtual void ResetSettings() = 0;

};

#endif // CONTROLLER_INTERFACE_H
