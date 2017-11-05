#include <QString>
#include <QtTest>
#include "heatercontroller.h"

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
  HeaterController* hc = new HeaterController();
  QVERIFY2(hc != 0, "Failure");
}

void HeatercontrollerTest::HeaterController_StartController()
{
  HeaterController hc = HeaterController();
  hc.StartController();
  QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(HeatercontrollerTest)

#include "tst_heatercontrollertest.moc"
