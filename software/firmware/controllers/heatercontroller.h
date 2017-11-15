#ifndef HEATERCONTROLLER_H
#define HEATERCONTROLLER_H

#include <QThread>
#include "hal.h"


class HeaterController : public QObject
{
Q_OBJECT

public:
  explicit HeaterController(QObject* parent = Q_NULLPTR);
  ~HeaterController();
  //int StartController();
  //QThread* Controller = nullptr;

private:
  HAL* pHal = Q_NULLPTR;
};

#endif // HEATERCONTROLLER_H
