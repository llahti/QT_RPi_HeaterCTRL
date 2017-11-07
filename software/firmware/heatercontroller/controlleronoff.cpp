#include "controlleronoff.h"
#include <iostream>

ControllerONOFF::ControllerONOFF(QObject* parent)
{
  this->setParent(parent);
}

void ControllerONOFF::run()
{
  while(!stopThread)
    {
      std::cout<<"Running...." << std::endl;
      this->sleep(1000); // Wait 1000msec
    }
  this->exit(0);
}
