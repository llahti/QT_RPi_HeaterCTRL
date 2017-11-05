#ifndef HEATERDATA_H
#define HEATERDATA_H

#include "heaterconfig.h"
#include "heaterstatus.h"

class HeaterData
{

public:
  HeaterData();

  HeaterConfig config;
  HeaterStatus status;
};

#endif // HEATERDATA_H
