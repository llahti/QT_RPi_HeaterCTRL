#include "controllerplugin.h"

ControllerPlugin::ControllerPlugin()
{

}

void ControllerPlugin::run()
{

}


ControllerPlugin::ControllerPlugin(HeaterData* pHeaterdata)
{
  this->heaterdata = pHeaterdata;
}


