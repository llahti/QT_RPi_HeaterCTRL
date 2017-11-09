#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include "circulationpump.h"
#include "hal.h"

class CirculationPumpTest : public QObject
{
  Q_OBJECT

public:
  CirculationPumpTest();

private Q_SLOTS:
  void Constructor_Destructor();
};

CirculationPumpTest::CirculationPumpTest()
{
  HAL *pHAL = new HAL();
  pHAL->setHWType("hal_dummy");
  int ret = pHAL->init();
  QVERIFY2(ret == 0, "pHAL.init() didn't return 0");

  CirculationPump *pump = new CirculationPump();
  QVERIFY2(pump != 0, "Failed to create new CirculationPump()");
  delete pump;
}

void CirculationPumpTest::Constructor_Destructor()
{
  QVERIFY2(true, "Failure");
}

QTEST_MAIN(CirculationPumpTest)

#include "tst_circulationpumptest.moc"
