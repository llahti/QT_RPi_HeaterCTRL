#ifndef HAL_H
#define HAL_H

#include "hal_interface.h"
#include <QString>
#include <string>
#include <QMutex>
#include <QThread>
#include <QTimer>
#include <QDebug>

class HAL : public QThread
{
Q_OBJECT

public:
  explicit HAL(QObject *parent = Q_NULLPTR);
  ~HAL();
  QString getHWType();
  int init();
  HAL_interface* HALinstance() { return this->HAL_instance; }
  int setHWType(QString hwtype);
  int startUpdates(const double period=1);  // time in seconds
  void stopUpdates();


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
  //QTimer* timer = nullptr;
  void run();
  int period_ms;
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
