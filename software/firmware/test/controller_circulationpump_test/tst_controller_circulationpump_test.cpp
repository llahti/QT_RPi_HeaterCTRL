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

QTEST_MAIN(Controller_circulationpump_test)

#include "tst_controller_circulationpump_test.moc"
