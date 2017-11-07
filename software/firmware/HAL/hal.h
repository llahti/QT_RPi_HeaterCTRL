#ifndef HAL_H
#define HAL_H

#include "hal_interface.h"
#include <QString>
#include <string>
#include <QMutex>
#include <QThread>
#include <QTimer>




class HAL : public QObject
{
Q_OBJECT

public:
  //HAL(QString hwtype);
  HAL(QObject *parent = Q_NULLPTR);
  ~HAL();
  QString getHWType();
  int init();
  HAL_interface* HALinstance() { return this->HAL_instance; }
  int setHWType(QString hwtype);
  int startTimer(const double period=1000);
  void stopTimer();


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
  void setCirculationPump(const bool state);
  void setExtFanSpeed(const double value);
  void updateValues();

private:
  // Store pointer to device specific HAL
  HAL_interface* HAL_instance = nullptr;
  // Keep information of hardware type
  QString hwType;
  // Timer for updating values
  QTimer* valueUpdater = nullptr;
};

enum HALErrors {
  NoError = 0,
  AlreadyInitialized,
  HWTypeNotSet,
  HWTypeNotRecognized,
  UnknownError,
  HALNotInitialized,
  TimerAlreadyRunning
};

#endif // HAL_H
