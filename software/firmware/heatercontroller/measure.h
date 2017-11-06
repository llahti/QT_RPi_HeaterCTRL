#ifndef MEASURE_H
#define MEASURE_H

#include "hal.h"
#include <QThread>
#include <iostream>

class Measure : public QThread
{
Q_OBJECT

public:
  Measure(HAL* pHAL);
  Measure(HAL* pHAL, double measPeriod);
  double getMeasPeriod();
  void run();
  void setMeasPeriod(double measPeriod);

signals:
  void measBoilerTemp(double temperature);
  void measExtGasTemp(double temperature);

public slots:
  void printData(double data) {std::cout << "printData() data=" << data << std::endl;}

private:
  HAL* pHAL;  // Pointer to HAL instance
  double period = 1.0;  // Measurement period
  bool stopFlag = false;
};

#endif // MEASURE_H
