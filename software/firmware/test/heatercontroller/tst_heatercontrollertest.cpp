#include <QString>
#include <QtTest>
#include <iostream>

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
  // Test that constructor is initializing contained pointers as NULL
  //HeaterController hc(this);
  HeaterController* hc = new HeaterController(this);
  QVERIFY2(hc != 0, "Failure to create HeaterController");
  QVERIFY2(hc->Controller == 0, "hc->Controller should be NULL");
}

void HeatercontrollerTest::HeaterController_StartController()
{
  HeaterController hc(this);
  hc.StartController();
}


QTEST_APPLESS_MAIN(HeatercontrollerTest)

#include "tst_heatercontrollertest.moc"
