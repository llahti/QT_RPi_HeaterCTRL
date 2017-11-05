#ifndef HEATERCONFIG_H
#define HEATERCONFIG_H

#include <QString>
#include <QSettings>
#include <string>

#ifndef COMPANYNAME
  #define COMPANYNAME "LauriLahti"
#endif
#ifndef APPNAME
  #define APPNAME "HeaterController"
#endif


class HeaterConfig
{
public:
  HeaterConfig();
  void resetFactoryDefaults();  // Resets all settings to factory default
  QSettings* getSettings();  // Returns pointer to settings object
private:


};

#endif // HEATERCONFIG_H
