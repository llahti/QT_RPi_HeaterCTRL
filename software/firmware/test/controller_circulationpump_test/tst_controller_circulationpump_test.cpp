#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QSignalSpy>

#include "hal.h"
#include "controller_interface.h"
#include "controller_circulationpump.h"

class Controller_circulationpump_test : public QObject
{
    Q_OBJECT

public:
    Controller_circulationpump_test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void ResetSettings();
    void RefreshSettings();
    void Initialize();
    void ProcessMeasurement();

private:
    HAL *m_pHAL = Q_NULLPTR;
    Controller_CirculationPump *m_pC_CP = Q_NULLPTR;

    // Group name for settings
    const QString m_settingsGroup = "CirculationPump";

};

Controller_circulationpump_test::Controller_circulationpump_test()
{
}

void Controller_circulationpump_test::initTestCase()
{
    // Initialize HAL
    m_pHAL = new HAL();
    m_pHAL->setHWType("hal_dummy");
    int ret = m_pHAL->init();
    QCOMPARE(ret, 0);

    // Initialize Controller
    m_pC_CP = new Controller_CirculationPump();
}

void Controller_circulationpump_test::cleanupTestCase()
{
    delete m_pHAL;
}

void Controller_circulationpump_test::ResetSettings()
{

  // First remove all entries
  QSettings settings(COMPANYNAME, APPNAME);
  settings.clear();
  settings.remove(m_settingsGroup);
  // Verify that all CirculationPump group does not exist
  // Need to extract all child groups and check whether "CirculationPump"
  // is included
  QStringList groups = settings.childGroups();
  QVERIFY(groups.contains(m_settingsGroup) == false);

  // Then Reset all settings
  m_pC_CP->ResetSettings();

  // Check that settings exist and that those are of correct value
  QCOMPARE(settings.value(m_settingsGroup + QString("/Version")).toInt(), 0);
  QCOMPARE(settings.value(m_settingsGroup + QString("/AutoControl")).toBool(), true);
  QCOMPARE(settings.value(m_settingsGroup + QString("/StartTemperature")).toDouble(), 80.0);
  QCOMPARE(settings.value(m_settingsGroup + QString("/StopTemperature")).toDouble(), 75.0);

  // Check that we have correct amount of keys
  // This ensurest that we have tested all keys
  settings.beginGroup(m_settingsGroup);
  QStringList keys = settings.childKeys();
  settings.endGroup();
  QCOMPARE(keys.count(), 4);
}

void Controller_circulationpump_test::RefreshSettings()
{
  // Set defaults
  //m_pC_CP->ResetSettings();

  // Set new values
  QSettings settings(COMPANYNAME, APPNAME);
  settings.beginGroup(m_settingsGroup);
  settings.setValue("Version", 1);
  settings.setValue("AutoControl", false);
  settings.setValue("StartTemperature", 70.0);
  settings.setValue("StopTemperature", 60.0);
  settings.endGroup();

  // Read settings values onto instance
  m_pC_CP->RefreshSettings();

  // Check that settings exist and that those are of correct value
  QCOMPARE(settings.value(m_settingsGroup + QString("/Version")).toInt(), 1);
  QCOMPARE(settings.value(m_settingsGroup + QString("/AutoControl")).toBool(), false);
  QCOMPARE(settings.value(m_settingsGroup + QString("/StartTemperature")).toDouble(), 70.0);
  QCOMPARE(settings.value(m_settingsGroup + QString("/StopTemperature")).toDouble(), 60.0);

  // Set defaults
  m_pC_CP->ResetSettings();
  m_pC_CP->RefreshSettings();
}

void Controller_circulationpump_test::Initialize()
{
  // 1. Test that missing settings are reset
  QSettings settings(COMPANYNAME, APPNAME);
  QStringList keys {"Version", "AutoControl", "StartTemperature", "StopTemperature"};
  for (auto s: keys) {
    m_pC_CP->ResetSettings();  // Reset to known state
    // Remove one by one
    settings.remove(m_settingsGroup + "/" + s);
    m_pC_CP->Initialize();
    QVERIFY(settings.contains(m_settingsGroup + "/" + s));
  }

  // 2. Check that existing settings are not affected
  m_pC_CP->ResetSettings();  // Reset to known state
  // Set Values to something else than default
  settings.beginGroup(m_settingsGroup);
  settings.setValue("Version", 1);
  settings.setValue("AutoControl", false);  // default is true
  settings.setValue("StartTemperature", 90.0);
  settings.setValue("StopTemperature", 80.0);
  settings.endGroup();
  // Check that values are still same after initialize
  m_pC_CP->Initialize();
  QCOMPARE(settings.value(m_settingsGroup + QString("/Version")).toInt(), 1);
  QCOMPARE(settings.value(m_settingsGroup + QString("/AutoControl")).toBool(), false);
  QCOMPARE(settings.value(m_settingsGroup + QString("/StartTemperature")).toDouble(), 90.0);
  QCOMPARE(settings.value(m_settingsGroup + QString("/StopTemperature")).toDouble(), 80.0);

  // Finally reset to known state
  m_pC_CP->ResetSettings();
}

void Controller_circulationpump_test::ProcessMeasurement()
{
  double stop_temp = 80;
  double start_temp = 85;
  // First set known settings
  QSettings settings(COMPANYNAME, APPNAME);
  settings.beginGroup(m_settingsGroup);
  settings.setValue("Version", 0);
  settings.setValue("AutoControl", true);  // default is true
  settings.setValue("StartTemperature", start_temp);
  settings.setValue("StopTemperature", stop_temp);
  settings.endGroup();
  settings.sync();

  // Setup test
  bool newState;
  m_pC_CP->Initialize();
  QSignalSpy spy(m_pC_CP, SIGNAL(stateChanged(bool)));
  QVariant arg;

  // Create a meas pack
  MeasurementPackage meas;
  meas.sensor_location = MeasurementPackage::SensorLocation::Boiler;
  meas.sensor_type_ = MeasurementPackage::SensorType::TEMP_PT100;


  // Build measurement for case 1
  meas.timestamp_ =  QDateTime::currentDateTime();
  meas.raw_measurements_.clear();
  meas.raw_measurements_.append(QVariant(double(stop_temp - 0.1)));

  // 1. Check that measurement below the stop limit will stop pump
  m_pC_CP->ProcessMeasurement(meas);
  qApp->processEvents();
  spy.wait();
  arg = spy.takeFirst().at(0);
  newState = arg.toBool();
  QCOMPARE(newState, false);

  // Build measurement for case 2
  meas.timestamp_ =  QDateTime::currentDateTime();
  meas.raw_measurements_.clear();
  meas.raw_measurements_.append(QVariant(double(start_temp + 0.1)));

  // 2. Check that measurement above start limit will start pump
  m_pC_CP->ProcessMeasurement(meas);
  qApp->processEvents();
  spy.wait();
  arg = spy.takeFirst().at(0);
  newState = arg.toBool();
  QCOMPARE(newState, true);

  // Build measurement for case 3
  meas.timestamp_ =  QDateTime::currentDateTime();
  meas.raw_measurements_.clear();
  meas.raw_measurements_.append(QVariant(double(start_temp + stop_temp)/2.0));

  // 3. Check that measurement between start and stop limits will not affect pump state
  m_pC_CP->ProcessMeasurement(meas);  // center of limits
  qApp->processEvents();
  spy.wait();
  arg = spy.takeFirst().at(0);
  newState = arg.toBool();
  QCOMPARE(newState, true);  // Should be true if last state have been true

  //QVERIFY2(false, "Test not implemented yet.");
}

QTEST_MAIN(Controller_circulationpump_test)

#include "tst_controller_circulationpump_test.moc"
