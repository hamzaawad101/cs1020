#include "participant.h"
#include <cmath>
using std::ostream;
using std::endl;
using std::cout;
Participant::Participant() {
    lastName =" ";
    firstName =" ";
    key=" ";
    height = 0;
    NumOfActivities = 0;
}
Participant::Participant(string lastName, string firstName) {
    this->lastName = lastName;
    this->firstName = firstName;
    setKey();
    height=0;
    NumOfActivities=0;
}

void Participant::setKey() {
       int length=lastName.length();
        lastName[0]=toupper(lastName[0]);
        for(int i=1;i<length;i++){
            lastName[i]=tolower(lastName[i]);
        }
        int len=firstName.length();
        firstName[0]=toupper(firstName[0]);
        for(int i=1;i<len;i++){
            firstName[i]=tolower(firstName[i]);
        }


    key=lastName + " "+firstName;
}
void  Participant::setActivities(const Activity& a){
      if(NumOfActivities<365){
        activities[NumOfActivities]=a;
        NumOfActivities++;
      }

}



void Participant::setLastName(const string last) {
        lastName=last;

}


void Participant::setFirstName(const string first) {
    firstName=first;
        int length=firstName.length();
        firstName[0]=toupper(firstName[0]);
        for(int i=1;i<length;i++){
            firstName[i]=tolower(firstName[i]);
        }


}


void Participant::setHeight(double h){
    if(h<0){
        height=0;
    }
    else{
        height=h;
        
}
}


void Participant::setNumOfActivities(int num){
        NumOfActivities=num;
    
}
// Copy constructor
Participant::Participant(const Participant& p) {
    setLastName(p.lastName);
    setFirstName(p.firstName);
    setNumOfActivities(p.NumOfActivities);
    setHeight(p.height);
    setKey();
    for(int i=0;i<NumOfActivities;i++){
        activities[i]=p.activities[i];
    }

}

double Participant::calcMiles() const{
    double miles=0;
    for(int i=0;i<NumOfActivities;i++){
        miles+=activities[i].Distance(height);
    }
    return miles;
}
bool operator<(const Participant& p1,const Participant& p2) {
    return (p1.key) < (p2.key);
}

bool operator==(const Participant& p1,const Participant& p2){
    return (p1.key)==(p2.key);
}
istream& operator>>(istream& in, Participant& p) {
    in>>p.firstName>>p.lastName>>p.height>>p.NumOfActivities;
    Activity temp;
    int t;
    for(int i=0;i<p.NumOfActivities;i++){
          in>>t;
          temp.setActivity(t);
          in>>t;
          temp.setTimes(t);
          p.activities[i]=temp;
    }
return in;
}    
istream& Participant::read(istream& input){
        participant_t p;
        input.read( (char*)&p, sizeof(participant_t));
        lastName=p.lastName;
        firstName=p.firstName;
        setKey();
        height = p.height;
        NumOfActivities= p.NumOfActivities;
        memcpy ( activities, p.activity, sizeof(Activity)*365);
        return input;

}
ostream& Participant::write( ostream& outBin) const {
        participant_t p;
        strcpy( p.firstName, firstName.c_str() );
        strcpy( p.lastName, lastName.c_str() );
        memcpy ( p.activity, activities, sizeof(Activity)*365);
        p.height = height;
        p.NumOfActivities= NumOfActivities;
        outBin.write( (char*)&p, sizeof(participant_t) );
        return outBin;
}
ostream& operator<<(ostream& out, const Participant& p) {
        out.setf(std::ios::showpoint|std::ios::fixed);
        out.precision(2);
    out << p.getFirstName() << " " << p.getLastName()<<" "<<p.calcMiles()<<endl;
    
    return out;
}