#ifndef HEATER_CONTROLLER_H
#define HEATER_CONTROLLER_H

#include <QObject>
#include <QSharedDataPointer>

class heater_controllerData;

class heater_controller : public QObject
{
  Q_OBJECT
public:
  explicit heater_controller(QObject *parent = nullptr);
  heater_controller(const heater_controller &);
  heater_controller &operator=(const heater_controller &);
  ~heater_controller();

signals:

public slots:

private:
  QSharedDataPointer<heater_controllerData> data;
};

#endif // HEATER_CONTROLLER_H