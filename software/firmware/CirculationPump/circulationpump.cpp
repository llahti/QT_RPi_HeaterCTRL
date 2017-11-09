#include "circulationpump.h"


CirculationPump::CirculationPump(QObject *parent) : QThread(parent)
{

}

CirculationPump::~CirculationPump()
{
  m_pHAL = nullptr;

  // Wait till thread is stopped
  if (this->isRunning()) {
    this->requestInterruption();
    this->quit();
    this->wait();
    }
}

int CirculationPump::setHAL(HAL *pHAL)
{
  m_pHAL = pHAL;
  return (bool)connect(this, SIGNAL(stateChanged(bool)),
                       pHAL, SLOT(setCirculationPump(bool)));

}

/**
 * @brief CirculationPump::value
 * @param value
 *
 * This method can be used for testing purposes to check that signal is sent to slot
 */
int CirculationPump::value(bool value)
{
  emit stateChanged(value);
  return 0;
}
