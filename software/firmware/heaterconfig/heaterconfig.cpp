#include "heaterconfig.h"

HeaterConfig::HeaterConfig(QObject *parent)
{
  this->setParent(parent);
}

void HeaterConfig::resetFactoryDefaults()
{
  QSettings settings(COMPANYNAME, APPNAME);
  // Circulation Pump settings
  // *************************
  settings.setValue("CirculationPump/AutoControl", true);  // Defines whether controller is turned on/off automatically
  settings.setValue("CirculationPump/StartTemperature", 80.0);  // Pump starting temperature
  settings.setValue("CirculationPump/StopTemperature", 75.0);  // Pump stop temperature

  // Boiler
  // ******
  settings.setValue("Boiler/MaxTemp", 97.0);  // Maximum allowed water temperature in boiler. If this is exeeded then turn off fan
  settings.setValue("Boiler/TargetTemp", 90.0);
  settings.setValue("Boiler/FireOffTemp", 80.0);  // When ext.gas temp is below this during to running it should be considered that the fire is off

  // Control method for exthaust fan.  Possibilities are: "switch", "pid"
  settings.setValue("Boiler/ControlMethod", "onoff");

  // Start Procedure settings
  settings.setValue("Boiler/Start/Duration", 1200);  // Start procedure duration in seconds
  settings.setValue("Boiler/Start/FireOnTemp", 100.0);  // If ext.gas temp is above this then fire is on
  settings.setValue("Boiler/Start/ExtFanSpeed", 65.0);

  //

  return;
}

QSettings* HeaterConfig::getSettings()
{
  QSettings* settings_obj = new QSettings(COMPANYNAME, APPNAME);
  //QSettings* settings_obj = nullptr;
  return settings_obj;
}

