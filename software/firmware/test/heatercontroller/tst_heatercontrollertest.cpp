#include <QString>
#include <QtTest>
#include <QThread>
#include <iostream>
#include <QSignalSpy>

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
}

void HeatercontrollerTest::HeaterController_StartController()
{
  HeaterController hc = HeaterController();
  hc.StartController();
  QVERIFY2(true, "Failure");
}


QTEST_APPLESS_MAIN(HeatercontrollerTest)

#include "tst_heatercontrollertest.moc"
