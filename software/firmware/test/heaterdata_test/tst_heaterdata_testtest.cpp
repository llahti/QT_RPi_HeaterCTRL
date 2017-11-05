#include <QString>
#include <QtTest>
#include <QSettings>
#include "../../heaterdata/heaterconfig.h"

class Heaterdata_testTest : public QObject
{
  Q_OBJECT

public:
  Heaterdata_testTest();

private Q_SLOTS:
  void heaterconfig();
  void resetFactoryDefaults();
  void getSettings();
};

Heaterdata_testTest::Heaterdata_testTest()
{
}

void Heaterdata_testTest::heaterconfig()
{
  QCOMPARE(COMPANYNAME, "LauriLahti");
  QCOMPARE(APPNAME, "HeaterController");
  HeaterConfig cfg = HeaterConfig();
}

void Heaterdata_testTest::resetFactoryDefaults()
{
  QVERIFY2(true, "Failure");
  QSettings settings(COMPANYNAME, APPNAME);
  settings.clear();

  HeaterConfig cfg = HeaterConfig();
  cfg.resetFactoryDefaults();

  // Verify that all keys are set
  QVERIFY2(settings.contains(QString("CirculationPump/UsePump")), "CirculationPump/UsePump - Not Found");
  QVERIFY2(settings.contains(QString("CirculationPump/StartTemperature")), "CirculationPump/StartTemperature - Not Found");
  QVERIFY2(settings.contains(QString("CirculationPump/StopTemperature")),  "CirculationPump/StopTemperature - Not Found");
  QVERIFY2(settings.contains(QString("ExtFan/ControlMethod")), "ExtFan/ControlMethod - Not Found");
  QVERIFY2(settings.contains(QString("ExtFan/MinSpeed")), "ExtFan/MinSpeed - Not Found");
  QVERIFY2(settings.contains(QString("ExtFan/PreferredSpeed")), "ExtFan/PreferredSpeed - Not Found");
  QVERIFY2(settings.contains(QString("ExtFan/MaxSpeed")), "ExtFan/MaxSpeed - Not Found");
  QVERIFY2(settings.contains(QString("ExtFan/StartSpeed")), "ExtFan/StartSpeed - Not Found");
  QVERIFY2(settings.contains(QString("ExtFan/StartDuration")),   "ExtFan/StartDuration - Not Found");
  QVERIFY2(settings.contains(QString("ExtFan/FireOnTemp")),  "ExtFan/FireOnTemp - Not Found");
  QVERIFY2(settings.contains(QString("Boiler/MaxTemp")),  "Boiler/MaxTemp - Not Found");
  QVERIFY2(settings.contains(QString("Boiler/TargetTemp")), "Boiler/TargetTemp - Not Found");
  // And there are exact amount of the keys
  //QVERIFY2(settings.allKeys().count() == 12, "Number of keys doesn't match");
}

void Heaterdata_testTest::getSettings()
{
  HeaterConfig cfg = HeaterConfig();
  QSettings* settings = cfg.getSettings();
  settings = cfg.getSettings();
  QString orgname(settings->organizationName());
  // Checking functionality of returned QSettings object by inspecting organiztion name
  QCOMPARE(QString(COMPANYNAME), orgname);
  delete settings;
}

QTEST_APPLESS_MAIN(Heaterdata_testTest)

#include "tst_heaterdata_testtest.moc"
