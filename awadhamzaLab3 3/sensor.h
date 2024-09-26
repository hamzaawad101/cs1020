#ifndef SENSOR_H
#define SENSOR_H
#include "timestamp.h"

class Sensor {
private:
    int sensorNumber;
    double mileMarker;
    Timestamp timestamp;

public:
    Sensor();
    Sensor(int num, double marker, const Timestamp& ts);
    int getSensorNumber() const {return sensorNumber;}
    double getMileMarker() const {return mileMarker;}
    void setSensorNumber(int num);
    void setMileMarker(double maker );
    void setTimeStamp(const Timestamp& ts);
    Timestamp getTimeStamp() const {return timestamp;}
    Sensor( const Sensor& s);
    Sensor operator=(const Sensor&);

};

#endif
                                                                                                                                                       

                                                                                                                                                       

