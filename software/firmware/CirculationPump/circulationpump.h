#ifndef CIRCULATIONPUMP_H
#define CIRCULATIONPUMP_H

#include <QThread>
#include <QObject>
#include "hal.h"

class CirculationPump : public QThread
{
Q_OBJECT

public:
  CirculationPump(QObject *parent = Q_NULLPTR);
  ~CirculationPump();
  //void run();
  int setHAL(HAL *pHAL);

protected:
  int value(bool value);

signals:
  void stateChanged(bool state);

private:
  HAL *m_pHAL = nullptr;
  int period_ms = 1767;
};


#endif // CIRCULATIONPUMP_H
