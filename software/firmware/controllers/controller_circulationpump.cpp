#include "controller_circulationpump.h"
#include <QDebug>
#include <QSettings>

Controller_CirculationPump::Controller_CirculationPump(QObject *parent)
  : Controller_Interface(parent)
{

}

void Controller_CirculationPump::Initialize()
{
  FixSettings();
  RefreshSettings();
}

void Controller_CirculationPump::ProcessMeasurement(const MeasurementPackage measpack)
{
  // Double check that the measurement is coming from correct place
  // and is of correct type
  if (measpack.sensor_type_ == MeasurementPackage::SensorType::TEMP_PT100
      && measpack.sensor_location == MeasurementPackage::SensorLocation::Boiler) {
    double boilerTemp = measpack.raw_measurements_.at(0).toDouble();
    if (boilerTemp > m_startTemperature) {
      //turn pump on
      emit stateChanged(true);
    }
    else if (boilerTemp < m_stopTemprerature) {
      //turn pump off
      emit stateChanged(false);
    }
  }
  else {
      qDebug()<< "Got incorrect measurement type or location";
    }

}

void Controller_CirculationPump::RefreshSettings()
{
  QSettings settings(COMPANYNAME, APPNAME);
  // Circulation Pump settings
  // *************************
  settings.beginGroup(m_settingsGroup);
  if (settings.value("Version").toInt() != m_version) {
      qDebug() << "Version number of settings storage and local controller doesn't match.";
      return;
  }
  else {
    m_autoControl = settings.value("AutoControl").toBool();
    m_startTemperature = settings.value("StartTemperature", 80.0).toDouble();
    m_stopTemprerature = settings.value("StopTemperature", 75.0).toDouble();
  }
  settings.endGroup();
}

void Controller_CirculationPump::ResetSettings()
{
  // First remove all entries
  QSettings settings(COMPANYNAME, APPNAME);
  settings.beginGroup(m_settingsGroup);
  settings.remove("");
  settings.endGroup();

  // Then call fix missing to add all missing keys and values
  FixSettings();
}

void Controller_CirculationPump::FixSettings()
{
  QSettings settings(COMPANYNAME, APPNAME);
  // Version
  settings.beginGroup(m_settingsGroup);
  #define VERSIONKEY "Version"
  if (!settings.contains(VERSIONKEY)) {
    settings.setValue(VERSIONKEY, m_version);  // Defines version of controller plugin
  }
  else if (settings.value("Version").toInt() != m_version) {
    qDebug() << "Setting's version does not match to class version.. Needs fixing";
  }

  // Autocontrol
  #define AUTOCONTROLKEY "AutoControl"
  if (!settings.contains(AUTOCONTROLKEY)) {
    settings.setValue(AUTOCONTROLKEY, true);  // Defines whether controller is turned on/off automatically
  }

  // Start Temperature
  #define STARTTEMPKEY "StartTemperature"
  if (!settings.contains(STARTTEMPKEY)) {
    settings.setValue(STARTTEMPKEY, 80.0);  // Pump starting temperature
  }

  // Stop Temperature
  #define STOPTEMPKEY "StopTemperature"
  if (!settings.contains(STOPTEMPKEY)) {
    settings.setValue(STOPTEMPKEY, 75.0);  // Pump stop temperature
  }
  settings.endGroup();
}
