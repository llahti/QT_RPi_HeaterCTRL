#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QThread>

class TimerTestExperimentTest : public QObject
{
  Q_OBJECT

public:
  TimerTestExperimentTest();

private Q_SLOTS:
  void timeout();
};

class PrintMessage : public QObject
{
  Q_OBJECT

public slots:
  void printMsg()
  {
    qDebug() << "Debug message";
  }
};

TimerTestExperimentTest::TimerTestExperimentTest()
{
}

void TimerTestExperimentTest::timeout()
{
  PrintMessage printer;
  QTimer timer;
  QSignalSpy spy(&timer, SIGNAL(timeout()));
  //timer.singleShot(0, &printer, SLOT(printMsg()));
  timer.singleShot(0, &timer, SLOT(timeout()));
  qApp->processEvents();
  spy.wait(2000);
  //#QThread::msleep(2000);
  qApp->processEvents();
  QCOMPARE(spy.count(), 1);
  QVERIFY2(true, "Failure");
}

QTEST_MAIN(TimerTestExperimentTest)

#include "tst_timertestexperimenttest.moc"
