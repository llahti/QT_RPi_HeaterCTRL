#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include "hal.h"
#include "controller_interface.h"
#include "controller_circulationpump.h"

class Controller_circulationpump_test : public QObject
{
    Q_OBJECT

public:
    Controller_circulationpump_test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();

private:
    HAL *m_pHAL = Q_NULLPTR;
    Controller_CirculationPump *m_pC_CP = Q_NULLPTR;

};

Controller_circulationpump_test::Controller_circulationpump_test()
{
}

void Controller_circulationpump_test::initTestCase()
{
    // Initialize HAL
    m_pHAL = new HAL();
    m_pHAL->setHWType("hal_dummy");
    int ret = m_pHAL->init();
    QCOMPARE(ret, 0);

    // Initialize Controller
    m_pC_CP = new Controller_CirculationPump();
}

void Controller_circulationpump_test::cleanupTestCase()
{
    delete m_pHAL;
}

void Controller_circulationpump_test::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(Controller_circulationpump_test)

#include "tst_controller_circulationpump_test.moc"
