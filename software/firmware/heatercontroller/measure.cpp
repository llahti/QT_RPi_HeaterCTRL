#include "measure.h"
#include <QThread>
#include <iostream>

Measure::Measure(HAL* pHAL)
{
  this->pHAL = pHAL;
}

Measure::Measure(HAL* pHAL, double period)
{
  this->pHAL = pHAL;
  this->setMeasPeriod(period);
}

double Measure::getMeasPeriod()
{
  return this->period;
}

void Measure::run()
{
  //std::cout << "Measure::run()" << std::endl;
  //while(!this->stopFlag) {
  while(!QThread::currentThread()->isInterruptionRequested()) {
    double boilerTemp;
    double extGasTemp;
    if (pHAL->measureBoilerTemp(boilerTemp)) {
      // Boiler temp reasurement failed
      std::cout << "Measure::run() ... Exit due to boiler temp" << std::endl;
      this->exit(1);
    }
    if (pHAL->measureExtGasTemp(extGasTemp)) {
      // Exthaust gas temperature measurement failed
      std::cout << "Measure::run() ... Exit due to ExtGasTemp" << std::endl;
      this->exit(1);
    }
    // Emit measurement results
    //std::cout << "Measure::run() ... emit measBoilerTemp(" << boilerTemp << ")" << std::endl;
    emit measBoilerTemp(boilerTemp);
    emit measExtGasTemp(extGasTemp);

    // period is in seconds so it need to be converted to msecs
    //std::cout << "Measure::run() ... before sleep" << std::endl;
    QThread::msleep(period*1000);
    //std::cout << "Measure::run() ... after sleep" << std::endl;
  }

  this->exit(0);
}

void Measure::setMeasPeriod(double measPeriod)
{
  this->period = measPeriod;
}

void Measure::stop()
{
  this->stopFlag = true;
}
