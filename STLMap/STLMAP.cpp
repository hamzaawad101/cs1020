/*
Author:Hamza awad
file:StudentLab.cpp
program: this program has a map of student and prints them in DescendingOrder using a DescendingOrder class comparator and
prints out the smallest student by last name. It also asks user for an id and searches map if found it print the information otherwise and error message.
*/
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
// our student class with variables and constructer.
class student{
    public:
	string ID;
     string FirstName;
        string LastName;
        double GPA;
        student(string first,string last,string id,double gpa){
        FirstName=first;
        LastName=last;
        ID=id;
	   GPA=gpa;
}
};

class DescendingOrder {
public:


 // overloaded  operator that compares two string and returns true if the first is greater than the second
bool operator()( string s1, string s2) const {
      return s1 > s2;
}
};

//bool function than compares a pair of a key and student value and returns true if the first pair lastname is smaller than the second pair.
bool compareStudents(const pair<string, student*>& p1, const pair<string, student*>& p2) {
    return p1.second->LastName < p2.second->LastName;
}
int main() {
	cout << "Hello!" << endl;
        string studentID="0";
//creat our map with key  value and student information we passed from the class.
        map<string, student*,DescendingOrder>  myMap;
                myMap["123"]=new student("Omar","Awad","123",3.4);
                myMap["707"]=new student("Hamza","Awad","707",3.5);
                myMap["789"]=new student ("sarah","Adkins","789",3.3);
                myMap["673"]=new student ("Adam","lam","673",3.9);
                myMap["652"]=new student ("Ally","Johnson","652",3.1);
                myMap["982"]=new student ("Ethan","Adams","982",4.0);
                myMap["210"]=new student ("kevin","Rudder","210",2.8);
                myMap["212"]=new student ("Shea","Bell","212",2.7);
                myMap["677"]=new student ("Billy","Simpson","677",3.7);
                myMap["532"]=new student ("Peter","Litheum","532",3.6);

//min iterator to iterate over the map and finds the minimum student using the compare function
        map<string, student*>::iterator minIt;
        minIt = min_element(myMap.begin(), myMap.end(),compareStudents);
        cout << "Minimum student: " << minIt->second->LastName << " "; 
        cout<<minIt->second->FirstName <<endl;
        map<string, student*>::iterator it;
        cout.setf(ios::showpoint|ios::fixed);
        cout.precision(1);
//for loop to print all map content in desending order
        for( it = myMap.begin(); it != myMap.end(); it++ ) {
          cout << "Student " << "ID: " <<it->second->ID << " ";
		 cout<< it->second->FirstName<<" " <<it->second->LastName<<" ";
          cout<<it->second->GPA<<endl;

   }
	map<string, student*>::iterator itr;
//do while loop that asks user to find student until user enters 0

        do{  cout<<"Enter Student ID for student you want to find: ";
                cin>>studentID;
                itr = myMap.find(studentID);
                if (itr != myMap.end()) {
                //print student info if found
                     cout << "Student " << studentID << ": ";
                     cout <<itr->second->LastName << ", ";
                     cout << itr->second->FirstName <<","; 
                     cout<< itr->second->GPA <<endl;
                }
                else {
                //student id not found
                  cout << "Student " << studentID << " not found." << endl;
                }
        }while(studentID!="0"); //user input 0 will quite the program
        cout << "Goodbye!" <<endl;
        return 0;
}
