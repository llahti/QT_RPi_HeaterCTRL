#include <QString>
#include <QSignalSpy>
#include <QtTest>
#include <iostream>
#include "hal.h"

class HALTest : public QObject
{
  Q_OBJECT

public:
  HALTest();

private Q_SLOTS:
  void constructor_empty();
  void init_with_dummyhal();
  void init_with_wrong_hwtype();
  void init_twice();
  void getsetHWType();
  void getHWType_notset();

  // Signal tests
  void signal_measuredBoilerTemp();
  void signal_measuredExtGasTemp();
  void signal_changedCirculationPumpState();
  void signal_changedExtFanSpeed();

  // public slots
  void publicslot_updateValues();
  void publicslot_setCirculationPump();
  void publicslot_setExtFanSpeed();

};

HALTest::HALTest()
{
}

void HALTest::constructor_empty()
{
  HAL hal(this);
  QVERIFY2(true, "Failure");
  HAL *phal = new HAL(this);
  QVERIFY2(phal != 0, "Can't create a new HAL instance");
  delete phal;
}


void HALTest::init_with_dummyhal()
{
  // Test with correct dummy hw
  HAL hal(this);
  hal.setHWType("hal_dummy");
  int ret = hal.init();
  QVERIFY2(ret == 0, "Init returned non-zero");
}

void HALTest::init_with_wrong_hwtype()
{
  // Test with correct dummy hw
  HAL hal(this);
  hal.setHWType("incorrect");
  int ret = hal.init();
  QVERIFY2(ret == 3, "Init didn't return 3");
}

void HALTest::init_twice()
{
  // Test with correct dummy hw
  HAL hal(this);
  hal.setHWType("hal_dummy");
  int ret = hal.init();
  ret = hal.init();
  QVERIFY2(ret == 1, "Init didn't return 1");
}

void HALTest::getsetHWType()
{
  // Test with correct "dummy hw"
  QString hwtype_set("hal_dummy");
  HAL hal(this);

  // Test that hwtype can be set before Init()
  int ret = hal.setHWType(hwtype_set);
  QVERIFY2(ret == 0, "setHWType didn't return 0");

  // Test that Init() runs correctly and HWtype is set
  QString hwtype_get = "";
  hwtype_get = hal.getHWType();
  ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");
  QCOMPARE(hwtype_set, hwtype_get);

  // Test that after init hwtype can't be set
  ret = hal.setHWType("this should not be saved");
  hwtype_get = hal.getHWType();
  QVERIFY2(ret == 1, "setHWType didn't return 1");
  QCOMPARE(hwtype_set, hwtype_get);
}

void HALTest::getHWType_notset()
{
  HAL hal(this);
  QString hwtype_get = hal.getHWType();
  int ret = hal.init();
  QVERIFY2(ret == 2, "Init didn't return 2");
  QVERIFY2(hwtype_get.isEmpty(), "hwtype is not empty (Should be)");
  QVERIFY2(!hwtype_get.isNull(), "hwtype is NULL. (Should not be)");
}

void HALTest::signal_measuredBoilerTemp()
{
  HAL hal(this);
  hal.setHWType("hal_dummy");
  int ret;

  // We are using QSignalSpy to capture emitted signals
  QSignalSpy spy(&hal, SIGNAL(measuredBoilerTemp(double)));
  ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");

  // Emit update signals
  hal.updateValues();
  // Check that we got one signal
  QVERIFY2(spy.count() == 1, "Didn't receive one signal");

  // Check for correct data value
  QList<QVariant> args = spy.takeFirst();  // Take first signal arguments
  double result = args.at(0).toDouble();
  QVERIFY2(80.5 == result, "Result was not 80.5");
}

void HALTest::signal_measuredExtGasTemp()
{
  HAL hal(this);
  hal.setHWType("hal_dummy");
  int ret;

  // We are using QSignalSpy to capture emitted signals
  QSignalSpy spy(&hal, SIGNAL(measuredExtGasTemp(double)));
  ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");

  // Emit update signals
  hal.updateValues();
  // Check that we got one signal
  QVERIFY2(spy.count() == 1, "Didn't receive one signal");

  // Check for correct data value
  QList<QVariant> args = spy.takeFirst();  // Take first signal arguments
  double result = args.at(0).toDouble();
  QVERIFY2(199.6 == result, "Result was not 199.6");
}

void HALTest::signal_changedCirculationPumpState()
{
  HAL hal(this);
  hal.setHWType("hal_dummy");
  int ret;

  // We are using QSignalSpy to capture emitted signals
  QSignalSpy spy(&hal, SIGNAL(changedCirculationPumpState(bool)));
  ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");

  // Emit update signals
  hal.updateValues();
  // Check that we got one signal
  QVERIFY2(spy.count() == 1, "Didn't receive one signal");

  // Check for correct data value
  QList<QVariant> args = spy.takeFirst();  // Take first signal arguments
  bool result = args.at(0).toBool();
  QVERIFY2(result, "Result was not true");
}

void HALTest::signal_changedExtFanSpeed()
{
  HAL hal(this);
  hal.setHWType("hal_dummy");
  int ret;

  // We are using QSignalSpy to capture emitted signals
  QSignalSpy spy(&hal, SIGNAL(changedExtFanSpeed(double)));
  ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");

  // Emit update signals
  hal.updateValues();
  // Check that we got one signal
  QVERIFY2(spy.count() == 1, "Didn't receive one signal");

  // Check for correct data value
  QList<QVariant> args = spy.takeFirst();  // Take first signal arguments
  double result = args.at(0).toDouble();
  QVERIFY2(result == 41.5, "Result was not 41.5");
}

void HALTest::publicslot_updateValues()
{
  HAL hal(this);
  hal.setHWType("hal_dummy");
  int ret;

  // We are using QSignalSpy to capture emitted signals
  QSignalSpy spy1(&hal, SIGNAL(changedExtFanSpeed(double)));
  QSignalSpy spy2(&hal, SIGNAL(measuredExtGasTemp(double)));
  QSignalSpy spy3(&hal, SIGNAL(changedCirculationPumpState(bool)));
  QSignalSpy spy4(&hal, SIGNAL(changedExtFanSpeed(double)));
  ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");

  // Emit update signals
  hal.updateValues();
  // Check that we got all signals
  QVERIFY2(spy1.count() == 1, "Didn't receive one signal");
  QVERIFY2(spy2.count() == 1, "Didn't receive one signal");
  QVERIFY2(spy3.count() == 1, "Didn't receive one signal");
  QVERIFY2(spy4.count() == 1, "Didn't receive one signal");
}

void HALTest::publicslot_setCirculationPump()
{
  HAL hal(this);
  hal.setHWType("hal_dummy");
  int ret;

  // We are using QSignalSpy to capture emitted signals
  QSignalSpy spy(&hal, SIGNAL(changedCirculationPumpState(bool)));
  ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");

  // 1. Test False setting
  hal.setCirculationPump(false);
  // Check that we got one signal
  QVERIFY2(spy.count() == 1, "Didn't receive one signal");

  // Check for correct data value
  QList<QVariant> args = spy.takeFirst();  // Take first signal arguments
  bool result = args.at(0).toBool();
  QVERIFY2(result == false, "Result was not false");

  // Test True setting
  hal.setCirculationPump(true);
  // Check that we got one signal
  QVERIFY2(spy.count() == 1, "Didn't receive one signal");

  // Check for correct data value
  QList<QVariant> args2 = spy.takeFirst();  // Take first signal arguments
  bool result2 = args2.at(0).toBool();
  QVERIFY2(result2 == true, "Result was not true");
}

void HALTest::publicslot_setExtFanSpeed()
{
  HAL hal(this);
  hal.setHWType("hal_dummy");
  int ret;

  // We are using QSignalSpy to capture emitted signals
  QSignalSpy spy(&hal, SIGNAL(changedExtFanSpeed(double)));
  ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");

  // Emit update signals
  hal.setExtFanSpeed(69.0);
  // Check that we got one signal
  QVERIFY2(spy.count() == 1, "Didn't receive one signal");

  // Check for correct data value
  QList<QVariant> args = spy.takeFirst();  // Take first signal arguments
  double result = args.at(0).toDouble();
  QVERIFY2(result == 69.0, "Result was not 41.5");
}


QTEST_APPLESS_MAIN(HALTest)
//QTEST_APPLESS_MAIN(HALTest)

#include "tst_haltest.moc"
