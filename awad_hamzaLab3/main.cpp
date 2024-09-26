/* Author Hamza Awad
This file reads in data of racers from file and Calculate how fast they finish the race and what time they pass a sensor
And prints out the information based on their time in acending order.
*/

#include <iostream>
#include <fstream>
#include <string>
#include "timestamp.h"
#include "racer.h"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>


 using std::cout;
 using std::cin;
 using std::endl;
 using std::sort;
 using std::vector;
 using std::ifstream;
 using std::string;
 using std::setw;
using std::left;
int main() {
   vector<Racer> Runner; //vector of racers 
   char filename[15];
   ifstream in; //input stream to read data
   char c;
   cout<<"Welcome to Racers-R-Us"<<endl;
   cout<<"Enter race file: ";
   cin>>filename;
   in.open(filename);
   if ( in.fail() ) {
       	cout<<"file does not exist"<<endl; //if file does not exist error message and return 
        return 1;      
   }
   else{
       in.get(c);
       if(in.eof()){
         cout<<filename<<" is empty"<<endl;  //if file is empty error message and return 
         return 1;
       }
       in.putback(c);

   }
   int sensors;
   double distance;
   Timestamp t;
   string temp;
    getline(in, temp); //this read the race information or start time sensor number and distance of the race into a string
    size_t found = temp.find(':');
    t.setHour(stoi(temp.substr(0, found))); //converts string to int 
    temp.erase(0, found+1);

    found = temp.find(':');
    t.setMinute(stoi(temp.substr(0, found)));
    temp.erase(0, found+1);

    found = temp.find(':');
    t.setSecond(stoi(temp.substr(0, found)));
    temp.erase(0, found+1);

    found = temp.find(';');
    t.setMillisecond(stoi(temp.substr(0, found)));
    temp.erase(0, found+1);

    found = temp.find(';');
    sensors=(stoi(temp.substr(0, found)));
    temp.erase(0, found+1);

    found = temp.find(';');
    distance=(stod(temp.substr(0, found))); //converts string to double 
    temp.erase(0, found+1);
    while(!in.eof()){
    Racer racer;
    in>>racer; //reads data into temp racer variable 
    racer.checkCheater(sensors);
    Runner.push_back(racer); //puts data into vector 
    }
    sort(Runner.begin(),Runner.end()); //sorts vector in accending order by time 
    cout << left <<setw(40) << "Name" << setw(15) << "Number" <<setw(10) << "Time" <<endl;
    cout<<"--------------------------------------------------------------"<<endl;
    for (int i = 0; i < Runner.size(); i++) {
            cout << Runner[i]<< endl; //prints vector information 
    
    }
    cout<<"Thank you for using Racers-R-Us. Happy Running!"<<endl;
    return 0;
}