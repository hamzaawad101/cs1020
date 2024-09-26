#include "activity.h"
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <cmath>
using namespace std;



Activity::Activity(){
    code=0;
    Time=0;
}

Activity::Activity(const Activity& a){
  setActivity(a.code);
  setTimes(a.Time);
}

void Activity::setActivity(const int a){

      if (a >= 0 && a <= 26) {
        code = a;
    }
}


void Activity::setTimes(const int m){
         if(m>0){
         Time=m;
       }
}

double Activity::Distance(double height) const{
     double PerMinute = STEPS[code]*Time;
    double FeetPerStep= ((0.413 * height) /12)*PerMinute;
    return FeetPerStep/ 5280.0;

}


