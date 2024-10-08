#ifndef TIMESTAMP_H
#define TIMESTAMP_H
#include <string>
using std::string;
using std::ostream;

class Timestamp {
private:
    int hour;
    int minute;
    int second;
    int millisecond;

public:
    Timestamp();
    Timestamp(const Timestamp&);
    virtual ~Timestamp (){}
    void setHour(const int& h);
    int getHour() const { return hour; }
    int getMinute() const {return minute;}
    void setMinute(const int& m);
    int getSecond() const {return second;}
    void setTimeStamp(string time);
    void setSecond(const int& s);
    int getMillisecond() const{return millisecond;}
    void setMillisecond(const int& ms);
    friend Timestamp operator-(const Timestamp& T1,const Timestamp& T2);
    friend ostream& operator<<( ostream& out , const Timestamp& Time );
    long timestamp2millisecond() const;
    void millisecond2timestamp(long ms);
    friend bool operator<(const Timestamp& T1 , const Timestamp& T2);
};


#endif
 