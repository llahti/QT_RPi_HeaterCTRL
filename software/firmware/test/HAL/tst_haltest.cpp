#include <QString>
#include <QSignalSpy>
#include <QtTest>
#include <iostream>

#include "hal.h"
#include "measurement_package.h"

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
  void start_stopUpdates();

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

void HALTest::start_stopUpdates()
{
    // Initialize
    HAL *pHAL = new HAL(this);
    pHAL->setHWType("hal_dummy");
    int ret = pHAL->init();
    QVERIFY2(ret == 0, "Init didn't return 0");

    // We are using QSignalSpy to capture emitted signals
    QSignalSpy spy1(pHAL, SIGNAL(measuredBoilerTemp(MeasurementPackage<double>)));
    QSignalSpy spy2(pHAL, SIGNAL(measuredExtGasTemp(MeasurementPackage<double>)));
    QSignalSpy spy3(pHAL, SIGNAL(changedCirculationPumpState(MeasurementPackage<bool>)));
    QSignalSpy spy4(pHAL, SIGNAL(changedExtFanSpeed(MeasurementPackage<double>)));

    // Start timer and and keep it running N cycles
    double period = 0.2;
    ret = pHAL->startUpdates(period);
    QVERIFY2(ret == 0, "Failed to start timer.");
    qApp->processEvents();


    // Wait till signal is received
    spy1.wait(1000.0 * period * 2);


    // Stopping updates
    pHAL->stopUpdates();

    // Check that we got all signals
    QVERIFY2(spy1.count() == 1, "spy1: Didn't receive 1 signal");
    QVERIFY2(spy2.count() == 1, "spy2: Didn't receive 1 signal");
    QVERIFY2(spy3.count() == 1, "spy3: Didn't receive 1 signal");
    QVERIFY2(spy4.count() == 1, "spy4: Didn't receive 1 signal");

    //QVERIFY2(pHAL->isFinished(), "Thread is not finished yet.");

    delete pHAL;
}

void HALTest::signal_measuredBoilerTemp()
{
  HAL hal(this);
  hal.setHWType("hal_dummy");
  int ret;

  // We are using QSignalSpy to capture emitted signals
  QSignalSpy spy(&hal, SIGNAL(measuredBoilerTemp(MeasurementPackage<double>)));
  ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");

  // Emit update signals
  hal.updateValues();
  // Check that we got one signal
  QVERIFY2(spy.count() == 1, "Didn't receive one signal");

  // Check for correct data value
  QList<QVariant> args = spy.takeFirst();  // Take first signal arguments
  MeasurementPackage<double> meas = args.at(0).value<MeasurementPackage<double>>();
  double result = meas.raw_measurements_.at(0);
  QVERIFY2(80.5 == result, "Result was not 80.5");
}

void HALTest::signal_measuredExtGasTemp()
{
  HAL hal(this);
  hal.setHWType("hal_dummy");
  int ret;

  // We are using QSignalSpy to capture emitted signals
  QSignalSpy spy(&hal, SIGNAL(measuredExtGasTemp(MeasurementPackage<double>)));
  ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");

  // Emit update signals
  hal.updateValues();
  // Check that we got one signal
  QVERIFY2(spy.count() == 1, "Didn't receive one signal");

  // Check for correct data value
  QList<QVariant> args = spy.takeFirst();  // Take first signal arguments
  MeasurementPackage<double> meas = args.at(0).value<MeasurementPackage<double>>();
  double result = meas.raw_measurements_.at(0);
  QVERIFY2(199.6 == result, "Result was not 199.6");
}

void HALTest::signal_changedCirculationPumpState()
{
  HAL hal(this);
  hal.setHWType("hal_dummy");
  int ret;

  // We are using QSignalSpy to capture emitted signals
  QSignalSpy spy(&hal, SIGNAL(changedCirculationPumpState(MeasurementPackage<bool>)));
  ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");

  // Emit update signals
  hal.updateValues();
  // Check that we got one signal
  QVERIFY2(spy.count() == 1, "Didn't receive one signal");

  // Check for correct data value
  QList<QVariant> args = spy.takeFirst();  // Take first signal arguments
  MeasurementPackage<bool> meas = args.at(0).value<MeasurementPackage<bool>>();
  bool result = meas.raw_measurements_.at(0);
  QVERIFY2(result, "Result was not true");
}

void HALTest::signal_changedExtFanSpeed()
{
  HAL hal(this);
  hal.setHWType("hal_dummy");
  int ret;

  // We are using QSignalSpy to capture emitted signals
  QSignalSpy spy(&hal, SIGNAL(changedExtFanSpeed(MeasurementPackage<double>)));
  ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");

  // Emit update signals
  hal.updateValues();
  // Check that we got one signal
  QVERIFY2(spy.count() == 1, "Didn't receive one signal");

  // Check for correct data value
  QList<QVariant> args = spy.takeFirst();  // Take first signal arguments
  MeasurementPackage<double> meas = args.at(0).value<MeasurementPackage<double>>();
  double result = meas.raw_measurements_.at(0);
  QVERIFY2(result == 41.5, "Result was not 41.5");
}

void HALTest::publicslot_updateValues()
{
  HAL hal(this);
  hal.setHWType("hal_dummy");
  int ret;

  // We are using QSignalSpy to capture emitted signals
  QSignalSpy spy1(&hal, SIGNAL(measuredBoilerTemp(MeasurementPackage<double>)));
  QSignalSpy spy2(&hal, SIGNAL(measuredExtGasTemp(MeasurementPackage<double>)));
  QSignalSpy spy3(&hal, SIGNAL(changedCirculationPumpState(MeasurementPackage<bool>)));
  QSignalSpy spy4(&hal, SIGNAL(changedExtFanSpeed(MeasurementPackage<double>)));
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
  QSignalSpy spy(&hal, SIGNAL(changedCirculationPumpState(MeasurementPackage<bool>)));
  ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");

  // 1. Test False setting
  hal.setCirculationPump(false);
  // Check that we got one signal
  qApp->processEvents();
  spy.wait(1000);
  QVERIFY2(spy.count() == 1, "Didn't receive one signal");

  // Check for correct data value
  QList<QVariant> args = spy.takeFirst();  // Take first signal arguments
  MeasurementPackage<bool> meas = args.at(0).value<MeasurementPackage<bool>>();
  bool result = meas.raw_measurements_.at(0);
  QVERIFY2(result == false, "Result was not false");

  // Test True setting
  hal.setCirculationPump(true);
  // Check that we got one signal
  qApp->processEvents();
  spy.wait(1000);
  QVERIFY2(spy.count() == 1, "Didn't receive one signal");

  // Check for correct data value
  QList<QVariant> args2 = spy.takeFirst();  // Take first signal arguments
  MeasurementPackage<bool> meas2 = args2.at(0).value<MeasurementPackage<bool>>();
  bool result2 = meas2.raw_measurements_.at(0);
  QVERIFY2(result2 == true, "Result was not true");
}

void HALTest::publicslot_setExtFanSpeed()
{
  HAL hal(this);
  hal.setHWType("hal_dummy");
  int ret;

  // We are using QSignalSpy to capture emitted signals
  QSignalSpy spy(&hal, SIGNAL(changedExtFanSpeed(MeasurementPackage<double>)));
  ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");

  // Emit update signals
  hal.setExtFanSpeed(69.0);
  // Check that we got one signal
  QVERIFY2(spy.count() == 1, "Didn't receive one signal");

  // Check for correct data value
  QList<QVariant> args = spy.takeFirst();  // Take first signal arguments
  MeasurementPackage<double> meas = args.at(0).value<MeasurementPackage<double>>();
  double result = meas.raw_measurements_.at(0);
  QVERIFY2(result == 69.0, "Result was not 69.0");
}


QTEST_MAIN(HALTest)
//QTEST_APPLESS_MAIN(HALTest)

#include "tst_haltest.moc"
