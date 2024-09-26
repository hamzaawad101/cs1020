#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "timestamp.h"
#include "sensor.h" 
#include "racer.h"


using std::size_t;
using std::cout;
using std::endl;
using std::setw;
using std::left;

// Default constructor

Racer::Racer(){
    
    RacerName="";
    RacerNumber = 0;
    totalTime = Timestamp();
    isCheater=false;
}
//set name 
void Racer::setName(string name) {
    RacerName = name;
}
//set number 
void Racer::setNumber(int n) {
    RacerNumber = n;
}
// set total time
void Racer::setTotalTime(Timestamp time) {
    totalTime = time;
    
}

// Copy constructor
Racer::Racer(const Racer& r) {
    setName(r.RacerName);
    setNumber(r.RacerNumber);
    setTotalTime(r.totalTime);
    isCheater=r.isCheater;
}
//sensor function to add sensor data to vector
void Racer::addSensorData(const Sensor &s){
            sensordata.push_back(s);
}

//Overloaded >> operator for reading input file

istream& operator>>(istream& in, Racer& r) {
             Sensor s;
             Timestamp time;
             string temp;
             getline(in, temp);
             size_t found = temp.find(';');
             r.setName(temp.substr(0, found));
             temp.erase(0, found+1);
             found = temp.find(';');
             r.setNumber(stoi(temp.substr(0, found)));
             temp.erase(0, found+1);
             
         //while look to read sesnor information and timestamp     
       while (found!=std::string::npos) {
              found=temp.find(';');
                s.setSensorNumber(stoi(temp.substr(0, found)));
                temp.erase(0, found+1);
                found = temp.find(';');
                s.setMileMarker(stod(temp.substr(0, found)));
                temp.erase(0, found+1);
                found = temp.find(';');
                Timestamp time;
                string str=temp.substr(0, found);
                time.setTimeStamp(str);
                temp.erase(0, found+1);
                s.setTimeStamp(time);
                r.addSensorData(s);
          
   }
   //calculate time it takes for racer to finish the race

        r.setTotalTime(r.sensordata.back().getTimeStamp()-r.sensordata.front().getTimeStamp());
            
    return in;
    
}
    
    //overloaded assinment operator
Racer& Racer::operator=(const Racer& r){
        if (this != &r) {
            RacerName=r.RacerName;
            RacerNumber = r.RacerNumber;
            totalTime = r.totalTime;
            isCheater=r.isCheater;
        }
       return *this;
}
//overloaded << operator or print out information
ostream& operator<<( ostream& out , const Racer& r ){
    if(r.isCheater){
    out<<"*";
    
       out << std::left << std::setw(39) << std::setfill(' ') << r.getName() << std::setw(10) << std::setfill(' ')<<std::left << r.getNumber() << std::setw(16) << r.getTotalTime();
    }
    else{
         out << std::left << std::setw(40) << std::setfill(' ')<< r.getName() << std::setw(10) << std::setfill(' ')<<std::left << r.getNumber() << std::setw(16) << r.getTotalTime();
    }
    return out;

}

//overloaded less than that compares racers time to finish the race

bool operator<(const Racer& r1, const Racer& r2){
    return r1.getTotalTime() < r2.getTotalTime();
}

//calculates how fast racer is going 
double calcTotalSpeed(const Sensor s1, const Sensor s2){
    Timestamp time1=s1.getTimeStamp()-s2.getTimeStamp();
    double mili =time1.timestamp2millisecond();
    double mili2= s1.getMileMarker()-s2.getMileMarker();
    mili/=(double)3600000;
    return mili2/mili;


}

void Racer::checkCheater(int n) {
    for (int i = 1; i < sensordata.size(); i++) {
        double speed = calcTotalSpeed(sensordata[i], sensordata[i-1]);
        if (speed > 14.0 || n!=sensordata.size()){
            isCheater = true;
            break;
        }
    }
}