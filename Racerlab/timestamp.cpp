#include "timestamp.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <iomanip>
using std::size_t;
using std::cout;
using std::endl;
using std::setw;
using std::left;
using namespace std;
void Timestamp::setTimeStamp(string time){

    size_t found;
    found = time.find(':');
    hour = stoi(time.substr(0, found));
    time.erase(0, found+1);

    found = time.find(':');
    minute = stoi(time.substr(0, found));
    time.erase(0, found+1);
   found = time.find(':');
    second = stoi(time.substr(0, found));
    time.erase(0, found+1);
  

    
   millisecond= stoi(time);
    


        
}




void Timestamp::setHour(const int& h) {
         if(h<0){
          hour=0;
        }
        else{
          hour = h;
        }
}



void Timestamp::setMinute(const int& m) {
        if(m<0 || m>59){
          minute = 0;
        }
        else{
         minute = m;
       }
}

void Timestamp::setSecond(const int& s) {
      if(s<0 || s>59){
         second=0;
      }
      else{
        second = s;
      }
}
void Timestamp::setMillisecond(const int& ms) {
       if(ms<0 || ms>=1000){
           millisecond=0;
       }
       else{
           millisecond = ms;
       }
}

Timestamp::Timestamp()  {
       hour=0;
       minute=0;
       second=0;
       millisecond=0;
}

Timestamp::Timestamp( const Timestamp& T ) {
   setHour( T.hour );
   setMinute( T.minute );
   setSecond( T.second );
   setMillisecond( T.millisecond );
}



Timestamp operator-(const Timestamp& T1 , const Timestamp& T2){
        long ms1,ms2,diff;
        Timestamp T;
        ms1=T1.timestamp2millisecond();
        ms2=T2.timestamp2millisecond();
        diff = ms1 - ms2;
        T.millisecond2timestamp(diff);
        return T;
}

void Timestamp::millisecond2timestamp(long ms){
    hour=ms/(60 * 60 * 1000);
    ms %=(60 * 60 * 1000);
    minute=ms/( 60 * 1000);
    ms %= (60 * 1000);
    second=ms/1000;
    ms %= 1000;
    millisecond=ms;
}

long Timestamp::timestamp2millisecond() const {
    long ms = 0;
    ms += hour * 60 * 60 * 1000;
    ms += minute * 60 * 1000;
    ms += second * 1000;
    ms += millisecond;
    return ms;
}
bool operator<(const Timestamp& T1 , const Timestamp& T2){
      return T1.timestamp2millisecond()<T2.timestamp2millisecond();
}
ostream& operator<<( ostream& out , const Timestamp& Time ){
  out <<std::right<<std::setw(2) << std::setfill('0') <<Time.getHour() << ":"<< std::setw(2) << std::setfill('0') << Time.getMinute()<< ":"<< std::setw(2) << std::setfill('0') <<Time.getSecond()<< ":"
      << std::setw(3) << std::setfill('0') << Time.getMillisecond();
  return out;
}

