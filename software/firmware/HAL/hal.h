#ifndef HAL_H
#define HAL_H

#include <QString>
#include <string>
#include <QMutex>
#include <QThread>
#include <QTimer>
#include <QDebug>

#include "hal_interface.h"
#include "measurement_package.h"

class HAL : public QObject
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
  void measuredBoilerTemp(MeasurementPackage<double> meas);
  void measuredExtGasTemp(MeasurementPackage<double> meas);
  void changedCirculationPumpState(MeasurementPackage<bool> meas);
  void changedExtFanSpeed(MeasurementPackage<double> meas);

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

  int m_timerid=0;

protected:
  void timerEvent(QTimerEvent *event) {updateValues();}
};

enum HALErrors {
  NoError = 0,
  AlreadyInitialized,
  HWTypeNotSet,
  HWTypeNotRecognized,
  UnknownError,
  HALNotInitialized,
  TimerAlreadyRunning,
  CantStartTimer
};

#endif // HAL_H
