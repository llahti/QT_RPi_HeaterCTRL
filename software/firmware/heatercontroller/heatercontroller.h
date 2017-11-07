#ifndef HEATERCONTROLLER_H
#define HEATERCONTROLLER_H

#include <QThread>
#include "hal.h"

class HeaterController : QObject
{
Q_OBJECT

public:
  HeaterController(QObject* parent = Q_NULLPTR);
  ~HeaterController();
  int StartController();
  QThread* Controller = nullptr;

private:
  HAL* hal = nullptr;
};

#endif // HEATERCONTROLLER_H
