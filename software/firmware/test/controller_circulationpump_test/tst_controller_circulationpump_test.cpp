#include <QString>
#include <QtTest>
#include <QCoreApplication>

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
  QVERIFY2(false, "Test not implemented yet.");
}

void Controller_circulationpump_test::ProcessMeasurement()
{
  QVERIFY2(false, "Test not implemented yet.");
}

QTEST_MAIN(Controller_circulationpump_test)

#include "tst_controller_circulationpump_test.moc"
