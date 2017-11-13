#ifndef CONTROLLER_CIRCULATIONPUMP_H
#define CONTROLLER_CIRCULATIONPUMP_H

#include <QObject>
#include <QString>

#include "controller_interface.h"
#include "measurement_package.h"
#include "app_globals.h"

class Controller_CirculationPump : public ControllerPlugin
{
  Q_OBJECT
public:
  explicit Controller_CirculationPump(QObject *parent = nullptr);
  void Initialize() override;

signals:
  void stateChanged(bool state);

public slots:
  void ProcessMeasurement(const MeasurementPackage measpack) override;
  void RefreshSettings() override;
  void ResetSettings() override;

private:
  void FixSettings();

  // Group name for settings
  const QString m_settingsGroup = "CirculationPump";

  // Settings.. Use relative safe settings.. just in case
  int m_version = 0;
  bool m_autoControl = true;
  double m_startTemperature = 70.0;
  double m_stopTemprerature = 65.0;
};

#endif // CONTROLLER_CIRCULATIONPUMP_H
