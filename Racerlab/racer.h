#ifndef RACER_H
#define RACER_H

#include "timestamp.h"
#include "sensor.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::ostream;
using std::istream;

class Racer {
private:
    string RacerName;
    int RacerNumber;
    Timestamp totalTime;
    bool isCheater;
    vector<Sensor> sensordata;

public:
    Racer();
    Racer(const Racer&);
    void setName(string name);
    string getName() const{return RacerName;}
    void setNumber(int n);
    int getNumber() const { return RacerNumber;}
    void setTotalTime(Timestamp time);
    Timestamp getTotalTime() const{return totalTime;}
    Sensor getSensorData(int i) const {return sensordata[i];}
    void addSensorData(const Sensor &s);
    void checkCheater(int n);
    friend double calcTotalSpeed(const Sensor s1, const Sensor s2);
    Racer& operator=(const Racer& r);
    friend ostream& operator<<(ostream& out, const Racer& r);
    friend istream& operator>>(istream& in, Racer& r);
    friend bool operator<(const Racer& r1, const Racer& r2);
};

#endif