#ifndef ACTIVITY_H
#define ACTIVITY_H 
 
 #include <string>
 using std::string;
 using std::ostream;
   const string ACTIVITY_NAMES[28] = {
    "Assembly Line", "Baseball","Basketball (shooting baskets)", "Basketball game","Bicycling under 10mph","Bicycling","Cooking", "Dance",
    "Football", "Hiking", "House cleaning","Gardening", "Miniature golf", "Racquetball", "Rowing","Running 6 mph", "Running 7 mph",
    "Running 8 mph", "Shopping","Soccer", "Softball","Stairs", "Swimming laps","Tennis", "Walking 3mph","Walking 4mph",
    "Weight lifting","Yoga",
    };

    const int STEPS[] = {
        85,152,136,242,121,242,61,167,242,182,91,99,91,212,212,303,348,409,70,212,152,273,212,212,100,152,121,76,
    };

class Activity {
private:
  int code;
  int Time;
public:
    Activity();
    ~Activity(){}
    Activity(const Activity& a);

    int getActivity() const{return code;}
    void setActivity(const int a);

    int getTime() const {return Time;}
    void setTimes(const int m);
    double Distance(double height) const;
}; 
#endif
