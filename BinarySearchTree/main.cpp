/* File: main.cpp
 * Author: Hamza awad
 * Descrption: Reads information from "tracking.bin" which is a binary file and reads it in to a binary tree. allows user to 
 add or remove content from the tree and save the changes.
 */
#include <fstream>
#include "participant.h"
#include "activity.h"
#include "binaryTree.h"
#include "position.h"
#include <iostream>
using namespace std;
int main() {
   //declare our variables 
   
   Participant p;
   BinarySearchTree<Participant> b;
   ifstream binIn;
   ofstream out;
   binIn.open( "tracking.bin", ios::in | ios::binary ); //the binary file we are getting information from
   if(!binIn.fail()){ //checks to see if the file exists and can be opened.
    while(p.read(binIn)){
      b.insert(p);
   }
    binIn.close(); //closes after done reading 
   }
   cout.setf(std::ios::showpoint|std::ios::fixed);
   cout.precision(2);
  string option;
    do { //prints out an option menu for the user
        cout <<"1 Remove participant" << endl;
        cout << "2 Add participant " << endl;
        cout << "3 Add activity " << endl;
        cout << "4 Calculate total miles walked " << endl;
        cout << "5 Pre-order print " << endl;
        cout << "6 Exit and save " << endl;
        cout << "Option> ";
        cin >> option;
         if(option=="1"){ 
        string lastName, firstName;
         cout << "Last Name: ";
         cin >> lastName;
         cout << "First Name: ";
         cin >> firstName;
    
       Participant temp(lastName, firstName);
         Position<Participant> pos = b.find(temp);
             if(!pos.isInternal()){ //if user wants to remove a participant the program checks if the participant is in the tree or not.
            cout<<"Participant "<<temp.getKey()<<" Not Found"<<endl;
         }else{
             temp=pos.getItem();
             b.erase(pos); //if participant is found they are erased using the BST erase function
             cout<<"Participant "<<temp.getKey()<<","<<temp.calcMiles()<<" total miles walked removed."<<endl;
          
         }
               
         }

         else if(option=="2"){
         string lastName, firstName;
         double height;
         cout << "Last Name: ";
         cin >> lastName;
         cout << "First Name: ";
         cin >> firstName;
         Participant temp(lastName, firstName);
         Position<Participant> pos = b.find(temp);
         if(pos.isInternal()){//if user wants to add participant the program checks if the participant is in the tree or not.
            cout << temp.getKey()<< " is already a participant." << endl;
         }else{
            //if not in the tree we ask for partiipant information;
            cout << "Height in inches: ";
             cin >> height; 
             if(height<0){
               cout<<"Please Enter valid height "<<endl;
                cout << "Height in inches: ";
                cin >> height; 
             }

             temp.setHeight(height);
              b.insert( temp); //they are added using the BST insert function
              cout <<temp.getKey() << " has been added." << endl;
         }
        }

        else if(option=="3"){
         string lastName, firstName;
         int input;
         Activity a;
         cout << "Last Name: ";
         cin >> lastName;
         cout << "First Name: ";
         cin >> firstName;
         Participant temp(lastName, firstName);
         Position<Participant> pos = b.find(temp);
         if(!pos.isInternal()){//if user wants to add an activity the program checks if the participant is in the tree or not.
            cout<<temp.getKey()<<" is not a participant"<<endl;
         }else{
            //if they are then we get their position and erase it.
            temp=pos.getItem();
            b.erase(pos);
            cout<<"Activity: ";
            cin>>input; //we take activity from user and add it and its time.
            a.setActivity(input);
            cout<<"Time: ";
            cin>>input;
            a.setTimes(input); // we use the set functions in the activity class to set the code and Time duration.
            temp.setActivities(a);
            b.insert(temp); //we use the insert function to add it.
            cout<<"Adding "<<temp.getKey()<<" "<<ACTIVITY_NAMES[a.getActivity()]<<" "<<a.getTime()<<" Minutes "<<" = "<<a.Distance(temp.getHeight())<<endl;

        }
         
        }
        else if(option=="4"){
           Position<Participant> pos=b.begin();
           double TotalMiles=0;
           for(;pos!=b.end();++pos){ //we loop over all participants in the tree and add up all their miles they have done

            TotalMiles+=pos.getItem().calcMiles();// for each item (participant) the calculate function is called.
            
           }
           cout<<"Total miles walked by *everyone* = "<<TotalMiles<<endl;
        }
         else if(option=="5"){//if user wants to print the participants in the tree 
            cout<<"Pre-order print"<<endl; 
            b.traverseAndPrint(b.root(),1); //print function is called with the type of print(Pre Order).
            cout<<endl;
        }
        else if(option=="6"){
            out.open("tracking.bin", ios::out | ios::binary);//to save changes the user made we open and write the changes to tracking.bin
            b.TraverseAndWrite(b.root(),out);
            out.close();
            cout<<"Exiting Program And Saving "<<endl;
        }
        else{
         cout<<"Please Enter Valid option from the menu below: "<<endl;
        }
      
 
    } while (option != "6");

    return 0;
}