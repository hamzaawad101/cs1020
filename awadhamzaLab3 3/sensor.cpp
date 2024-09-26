#include "sensor.h"
#include "timestamp.h"

Sensor::Sensor(int num, double marker, const Timestamp& ts) {
        sensorNumber = num;
        mileMarker = marker;
        timestamp = ts;
}
void Sensor::setSensorNumber(int num) {
        sensorNumber = num;
}


void Sensor::setMileMarker(double marker) {
        mileMarker = marker;
}
void Sensor::setTimeStamp(const Timestamp& ts) {
        timestamp = ts;
}

Sensor::Sensor() {
    sensorNumber = 0;
    mileMarker = 0.0;
}

Sensor::Sensor( const Sensor& s) {
            setSensorNumber( s.sensorNumber );
            setMileMarker( s.mileMarker );
            setTimeStamp( s.timestamp );


}
Sensor Sensor::operator=(const Sensor& s) {
        if (this !=&s) {
            sensorNumber= s.sensorNumber;
            mileMarker= s.mileMarker;
            timestamp = s.timestamp;
        }
            return *this;
}

