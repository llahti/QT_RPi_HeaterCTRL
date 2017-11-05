#include <QtTest>
#include "heaterdata.h"

// add necessary includes here

class readBoilerTemp : public QObject
{
  Q_OBJECT

public:
  readBoilerTemp();
  ~readBoilerTemp();

private slots:
  void test_case1();

};

readBoilerTemp::readBoilerTemp()
{

}

readBoilerTemp::~readBoilerTemp()
{

}

void readBoilerTemp::test_case1()
{

}

QTEST_APPLESS_MAIN(readBoilerTemp)

#include "tst_readboilertemp.moc"
