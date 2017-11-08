#include <QtTest>
#include <QCoreApplication>
#include <QObject>
#include <QThread>

#include "hal.h"

// add necessary includes here

class start_stop_Timer : public QObject
{
  Q_OBJECT

  QThread thread1;
public:
  start_stop_Timer();
  ~start_stop_Timer();

  HAL *pHAL;


private slots:
  void initTestCase();
  void cleanupTestCase();
  void test_case1();
};

start_stop_Timer::start_stop_Timer()
{

}

start_stop_Timer::~start_stop_Timer()
{

}

void start_stop_Timer::initTestCase()
{
  pHAL = new HAL(this);
  pHAL->setHWType("hal_dummy");
  int ret = pHAL->init();
  pHAL->moveToThread(&thread1);
  //thread1.start();
  QVERIFY2(ret == 0, "Init didn't return 0");

}

void start_stop_Timer::cleanupTestCase()
{
  delete pHAL;
  thread1.quit();
  thread1.wait();
}

void start_stop_Timer::test_case1()
{
  // We are using QSignalSpy to capture emitted signals
  QSignalSpy spy1(pHAL, SIGNAL(changedExtFanSpeed(double)));
  QSignalSpy spy2(pHAL, SIGNAL(measuredExtGasTemp(double)));
  QSignalSpy spy3(pHAL, SIGNAL(changedCirculationPumpState(bool)));
  QSignalSpy spy4(pHAL, SIGNAL(changedExtFanSpeed(double)));


  // Start timer and and keep it running 5 cycles
  //double period = 0.5;
  qDebug() << "Calling pHAL->startUpdates().";
  int ret = pHAL->startUpdates(1);
  thread1.start();
  QVERIFY2(ret == 0, "Failed to start timer.");
  qDebug() << "start sleep";
  QThread::sleep(5);
  qDebug() << "slept " << 10 << " seconds";

  // Stopping updates
  //pHAL->stopUpdates();


  // Check that we got all signals
  qDebug() << "start_stop_Timer::test_case1(): spy1.count="<<spy1.count();
  QVERIFY2(spy1.count() == 5, "spy1: Didn't receive 5 signals");
  QVERIFY2(spy2.count() == 5, "spy2: Didn't receive 5 signals");
  QVERIFY2(spy3.count() == 5, "spy3: Didn't receive 5 signals");
  QVERIFY2(spy4.count() == 5, "spy4: Didn't receive 5 signals");

}


QTEST_MAIN(start_stop_Timer)

#include "tst_start_stop_timer.moc"
