#include "heater_controller.h"

class heater_controllerData : public QSharedData
{
public:

};

heater_controller::heater_controller(QObject *parent) : QObject(parent), data(new heater_controllerData)
{

}

heater_controller::heater_controller(const heater_controller &rhs) : data(rhs.data)
{

}

heater_controller &heater_controller::operator=(const heater_controller &rhs)
{
  if (this != &rhs)
    data.operator=(rhs.data);
  return *this;
}

heater_controller::~heater_controller()
{

}
