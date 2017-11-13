#ifndef MEASUREMENT_PACKAGE_H_
#define MEASUREMENT_PACKAGE_H_

#include <QList>
#include <QDateTime>

/**
 * @brief The MeasurementPackage class
 * This class provides way to pack several measurement value with timestamp
 */
class MeasurementPackage {
public:
  QDateTime timestamp_;

  enum SensorType{
    TEMPERATURE,
    BOOLEAN
  } sensor_type_;

  QList raw_measurements_;

};

#endif /* MEASUREMENT_PACKAGE_H_ */

