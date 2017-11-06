#include <QString>
#include <QtTest>
#include <QThread>
#include <iostream>
#include <QSignalSpy>

#include "heatercontroller.h"
#include "measure.h"

class HeatercontrollerTest : public QObject
{
  Q_OBJECT

public:
  HeatercontrollerTest();

private Q_SLOTS:
  void initTestCase();
  void cleanupTestCase();
  void HeaterController_Constructor();
  void HeaterController_StartController();
  void Measure_Constructors();
  void Measure_set_get_measurePeriod();
  void Measure_run_and_stop_thread();
  void Measure_signal_measBoilerTemp();

};

class DummyData : public QObject
{
  Q_OBJECT
public:
  DummyData() {this->m_data = 0.0;}
  double getValue() const {return this->m_data;}

public slots:
  void setValue(double data)
  {
    this->m_data = data;
    std::cout << "DummyData::setValue() data=" << data << std::endl;
  }

private:
    double m_data;
};

HeatercontrollerTest::HeatercontrollerTest()
{
}

void HeatercontrollerTest::initTestCase()
{
}

void HeatercontrollerTest::cleanupTestCase()
{
}

void HeatercontrollerTest::HeaterController_Constructor()
{
  // Test that constructor is initializing contained pointers as NULL
  HeaterController* hc = new HeaterController();
  QVERIFY2(hc != 0, "Failure to create HeaterController");
  QVERIFY2(hc->Controller == 0, "hc->Controller should be NULL");
  QVERIFY2(hc->Measurement == 0, "hc->Measurement should be NULL");
}

void HeatercontrollerTest::HeaterController_StartController()
{
  HeaterController hc = HeaterController();
  hc.StartController();
  QVERIFY2(true, "Failure");
}

void HeatercontrollerTest::Measure_Constructors()
{
  // 1. Test that instances can be created correctly
  HAL* hal = new HAL("hal_dummy");
  Measure* meas = new Measure(hal);
  QVERIFY2(hal != 0, "1: Failed to create HAL instance");

  // 2. Test "Measure(HAL* pHAL)" Constructor
  QVERIFY2(meas != 0, "2: Failed to create Measure(HAL* pHAL) instance");
  QVERIFY2(meas->getMeasPeriod() == 1.0, "2: Measurement period is not 1.0");
  delete meas;

  // 3. Test "Measure(HAL* pHAL, double measPeriod)" Constructor
  double period = 2.0;
  meas = new Measure(hal, period);
  QVERIFY2(meas != 0, "3: Failed to create Measure(HAL* pHAL, double period) instance");
  QVERIFY2(meas->getMeasPeriod() == 2.0, "3: Measurement period is not 2.0");

  // Delete instances
  delete hal;
  delete meas;
}

void HeatercontrollerTest::Measure_set_get_measurePeriod()
{
  // Create HAL and Measure instances
  double period = 2;
  HAL* hal = new HAL("hal_dummy");
  //int ret = hal->init();
  Measure* meas = new Measure(hal, period);
  QVERIFY2(hal != 0, "Failed to create HAL instance");
  //QVERIFY2(ret == 0, "Failed to Init() hal instance");

  // 1. Test setting and getting measurement Period
  QVERIFY2(meas->getMeasPeriod() == 2.0, "1. Measurement period was not 2.0");
  meas->setMeasPeriod(4.0);
  QVERIFY2(meas->getMeasPeriod() == 4.0, "1. Measurement period was not 4.0");

  // Delete instances
  delete hal;
  delete meas;
}

void HeatercontrollerTest::Measure_run_and_stop_thread()
{
  // Create HAL and Measure instances
  double period = 0.2;
  HAL* hal = new HAL("hal_dummy");
  int ret = hal->init();
  QVERIFY2(ret == 0, "Failed to Init() hal instance");
  Measure* meas = new Measure(hal, period);

  // 1. Start measurement thread and check that it is running
  meas->start();
  QVERIFY2(meas->isRunning() == true, "Measurement thread is not running");

  // 2. Wait for 1 seconds and check that it is running
  QThread::sleep(1);
  QVERIFY2(meas->isRunning() == true, "Measurement thread is not running");

  // 3. Stop thread and check running status
  meas->requestInterruption();
  meas->quit();
  meas->wait();
  QVERIFY2(meas->isRunning() == false, "Measurement thread is still running");

  // Delete instances
  delete meas;
  delete hal;
}

void HeatercontrollerTest::Measure_signal_measBoilerTemp()
{
  // Create HAL, Measure and dummy instances
  double period = 0.2;
  HAL* hal = new HAL("hal_dummy");
  int ret = hal->init();
  QVERIFY2(ret == 0, "Failed to Init() hal instance");
  Measure* meas = new Measure(hal, period);

  // We are using QSignalSpy to capture emitted signals
  QSignalSpy spy(meas, SIGNAL(measBoilerTemp(double)));

  // Start measurement thread and stop if after few iterations
  meas->start();
  QThread::sleep(1);
  meas->requestInterruption();
  //QThread::msleep(200);
  meas->quit();
  meas->wait();

  // 1. Test that signal is received
  QVERIFY2(spy.count() > 1, "Didn't receive any signals");
  QList<QVariant> args = spy.takeFirst();  // Take first signal arguments
  double result = args.at(0).toDouble();
  QVERIFY2(result == 80.5, "1. Received data was not 80.5");

  // Delete instances
  delete meas;
  delete hal;
}

QTEST_APPLESS_MAIN(HeatercontrollerTest)

#include "tst_heatercontrollertest.moc"
