#ifndef HAL_H
#define HAL_H

#include "hal_interface.h"
#include <QString>
#include <string>
#include <QMutex>
#include <QThread>


class HAL : public QThread
{
Q_OBJECT

public:
  //HAL(QString hwtype);
  HAL(QObject *parent = Q_NULLPTR);
  int init();
  QString getHWType();
  int setHWType(QString hwtype);
  HAL_interface* HALinstance() { return this->HAL_instance;}

  // TODO: enum of error codes

  enum DataValues {
    BoilerTemp,
    ExtGasTemp,
    ExtFan,
    CirculationPump
  };

signals:
  void measuredBoilerTemp(const double value);
  void measuredExtGasTemp(const double value);
  void changedCirculationPumpState(const bool state);
  void changedExtFanSpeed(const double value);

public slots:
  void updateValues();
  void setCirculationPump(const bool state);
  void setExtFanSpeed(const double value);

private:
  // Store pointer to device specific HAL
  HAL_interface* HAL_instance = nullptr;
  // Keep information of hardware type
  QString hwType;
};

#endif // HAL_H
