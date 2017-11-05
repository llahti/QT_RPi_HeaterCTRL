#include "controlleronoff.h"
#include <iostream>

ControllerONOFF::ControllerONOFF()
{

}

//ControllerONOFF::ControllerONOFF(HeaterData* pHeaterdata)
//{
//  this->heaterdata = pHeaterdata;
//}

void ControllerONOFF::run()
{
  while(!stopThread)
    {
      std::cout<<"Running...." << std::endl;
      this->wait(1000); // Wait 1000msec
    }
  this->exit(0);
}
