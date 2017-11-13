#ifndef CONTROLLER_CIRCULATIONPUMP_H
#define CONTROLLER_CIRCULATIONPUMP_H

#include <QObject>

class Controller_CirculationPump : public QObject
{
  Q_OBJECT
public:
  explicit Controller_CirculationPump(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CONTROLLER_CIRCULATIONPUMP_H