#ifndef MEASUREMENT_PACKAGE_H_
#define MEASUREMENT_PACKAGE_H_

#include <QVector>
#include <QDateTime>
#include <QMetaType>
#include <QObject>

/**
 * @brief The MeasurementPackage class
 * This class provides way to pack several measurement values with timestamp
 */
template <class T>
class MeasurementPackage {
public:
  QDateTime timestamp_;

  enum SensorType{
    TEMP_PT100,
    BOOLEAN,
    PERCENTAGE
  } sensor_type_;

  enum SensorLocation {
    Boiler,
    ExtGas,
    CircPump,
    ExtFan
  } sensor_location;

  QVector<T> raw_measurements_;

};

Q_DECLARE_METATYPE(MeasurementPackage<bool>)
Q_DECLARE_METATYPE(MeasurementPackage<double>)
Q_DECLARE_METATYPE(MeasurementPackage<int>)
Q_DECLARE_METATYPE(MeasurementPackage<long>)
#endif /* MEASUREMENT_PACKAGE_H_ */

