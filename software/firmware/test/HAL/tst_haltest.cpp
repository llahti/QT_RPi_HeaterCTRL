#include <QString>
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
  void constructor_hwtype();
  void init_with_dummyhal();
  void init_without_hwtype();
  void init_with_wrong_hwtype();
  void init_twice();
  void getsetHWType();
  void getHWType_notset();
  void measureBoilerTemp();
  void measureExtGasTemp();
};

HALTest::HALTest()
{
}

void HALTest::constructor_empty()
{
  HAL hal();
  QVERIFY2(true, "Failure");
}

void HALTest::constructor_hwtype()
{
  HAL hal("hal_dummy");
  QVERIFY2(true, "Failure");
}

void HALTest::init_with_dummyhal()
{
  // Test with correct dummy hw
  HAL hal("hal_dummy");
  int ret = hal.init();
  QVERIFY2(ret == 0, "Init returned non-zero");
}

void HALTest::init_without_hwtype()
{
  // Test with non-existent hw-string
  HAL hal = HAL();
  int ret = hal.init();
  QVERIFY2(ret == 2, "Init didn't return 2 when hwtype string is non-existent");
}

void HALTest::init_with_wrong_hwtype()
{
  // Test with correct dummy hw
  HAL hal("incorrect");
  int ret = hal.init();
  QVERIFY2(ret == 3, "Init didn't return 3");
}

void HALTest::init_twice()
{
  // Test with correct dummy hw
  HAL hal("hal_dummy");
  int ret = hal.init();
  ret = hal.init();
  QVERIFY2(ret == 1, "Init didn't return 1");
}

void HALTest::getsetHWType()
{
  // Test with correct "dummy hw"
  QString hwtype_set("hal_dummy");
  HAL hal = HAL();

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
  HAL hal = HAL();
  QString hwtype_get = hal.getHWType();
  int ret = hal.init();
  QVERIFY2(ret == 2, "Init didn't return 2");
  QVERIFY2(hwtype_get.isEmpty(), "hwtype is not empty (Should be)");
  QVERIFY2(!hwtype_get.isNull(), "hwtype is NULL. (Should not be)");
  //QCOMPARE(hwtype_set, hwtype_get);
}

void HALTest::measureBoilerTemp()
{
  HAL hal = HAL("hal_dummy");
  double result;
  int ret;

  // 1. test that method gives correct return value for non-initialized HAL
  ret = hal.measureBoilerTemp(result);
  QVERIFY2(ret == 5, "measureBoilerTemp didn't return 0");

  // 2. test with correctly initialized HAL
  ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");
  ret = hal.measureBoilerTemp(result);
  QVERIFY2(ret == 0, "measureBoilerTemp didn't return 0");
  QVERIFY2(80.5 == result, "Result was not 80.5");
}

void HALTest::measureExtGasTemp()
{
  HAL hal = HAL("hal_dummy");
  int ret = hal.init();
  QVERIFY2(ret == 0, "Init didn't return 0");
  double result;
  ret = hal.measureExtGasTemp(result);
  QVERIFY2(ret == 0, "measureBoilerTemp didn't return 0");
  QVERIFY2(199.6 == result, "Result was not 80.5");
}


QTEST_APPLESS_MAIN(HALTest)

#include "tst_haltest.moc"
