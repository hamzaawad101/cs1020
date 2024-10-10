#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include "activity.h"
#include <string>
#include <iostream>

using std::string;
using std::ostream;
using std::istream;

class Participant {
private:
    string lastName;
    string firstName;
    string key;
    double height;
    Activity activities[365];
    int NumOfActivities;
public:
    Participant();
    Participant(const Participant& p);
    Participant(string lastName, string firstName);
    string  getLastName() const{return lastName;}
    void setLastName(const string last);
    string getFirstName() const{return firstName;}
    void setFirstName(const string first);
    void setHeight(double h);
    double getHeight() const{return height;}
    void setActivities(Activity a[]);
    void setNumOfActivities(int num);
    int getNumOfActivites() const{return NumOfActivities;}
    void setKey();
    double calcMiles()const;
    string getKey()const{return key;}
    Activity getActivities (int i) const {return activities[i];}
    void setActivities(const Activity& a);
    ostream& write( ostream& outBin)const;
    istream& read(istream& input);
    friend istream& operator>>(istream& in, Participant& p);
    friend  bool operator<(const Participant& p1,const Participant& p2);
    friend bool operator==(const Participant& p1,const Participant& p2);
    friend ostream& operator<<(ostream& out, const Participant& p);
};
typedef struct participant_t {
char firstName[128];
char lastName[128];
double height;
Activity activity[365];
int NumOfActivities;
} participant_t;

#endif