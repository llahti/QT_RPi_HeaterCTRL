#include "heaterconfig.h"

HeaterConfig::HeaterConfig(QObject *parent)
{
  this->setParent(parent);
}

void HeaterConfig::resetFactoryDefaults()
{
  QSettings settings(COMPANYNAME, APPNAME);
  // Circulation Pump settings
  settings.setValue(QString("CirculationPump/UsePump"), true);  // Defines whether controller is using pump
  settings.setValue("CirculationPump/StartTemperature", 80.0);  // Pump starting temperature
  settings.setValue("CirculationPump/StopTemperature", 75.0);  // Pump stop temperature

  // Exhaust Fan
  // Control method for exthaust fan.  Possibilities are: "switch", "pid"
  settings.setValue("ExtFan/ControlMethod", "switch");
  settings.setValue("ExtFan/MinSpeed", 20.0);
  settings.setValue("ExtFan/PreferredSpeed", 50.0);
  settings.setValue("ExtFan/MaxSpeed", 80.0);
  settings.setValue("ExtFan/StartSpeed", 65.0);
  settings.setValue("ExtFan/StartDuration", 1200);  // Start procedure duration in seconds
  settings.setValue("ExtFan/FireOnTemp", 100.0);  // If ext.gas temp is above this then fire is on

  // Boiler
  settings.setValue("Boiler/MaxTemp", 95.0);  // Maximum allowed water temperature in boiler. If this is exeeded then turn off fan
  settings.setValue("Boiler/TargetTemp", 90.0);

  return;
}

QSettings* HeaterConfig::getSettings()
{
  QSettings* settings_obj = new QSettings(COMPANYNAME, APPNAME);
  //QSettings* settings_obj = nullptr;
  return settings_obj;
}

