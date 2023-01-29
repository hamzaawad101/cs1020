/* file lab1.cpp
 author hamza awad
this code runs a small theater program that asks customer it's for how many tickets they would like to purchase and print out a receipt with a total, tax, an$
*/


#include <iostream>
using namespace std;

int main(){
	const double TICKET_PRICE = 9.95;         // we set our variables and set our const.
        const double TAX_RATE = 0.095;
        int seatingLeft = 300;
        string movieName = "The Best Movie Ever";
        string rating = "PG-13";
        int startHour = 4;
        int startMinute = 30;
        char ampm = 'P';
        int tickets;
        double subtotal, tax, total; //the receipt will print out numbers in double
        cout<<"Welcome to My Theater’s Ticketing Program." << endl;
        cout.precision(2);
        cout.setf(std::ios::showpoint);
        cout.setf(std::ios::fixed);
        while(tickets!=0 ){  // use a while loop to execte the program until it is ended by the user with an input of 0.
                cout<< "Today we are showing: The Best Movie Ever rated PG-13 at 4:30 PM" <<endl;
                cout << "How many tickets (0 to end ) ? " << endl;
                cin>>tickets;
                if(tickets==0){       //set our conditions with if statmetns and else if statment so it execute the condition based on input of user
                        break;
                }
                else if(seatingLeft==0){
                        cout<<"I'm sorry. We're SOLD OUT."<<endl;

                }
                else if(tickets<0){
                        cout<< "invalid number of tickets: "<<tickets<<endl;
                }
                else if (tickets <= seatingLeft) {	 //set our calculation for our double variables and const variables
                        subtotal=tickets*TICKET_PRICE;
                        tax=TAX_RATE*subtotal;
                        total=subtotal+tax;
                        cout<<"your subtotal is "<<subtotal<<endl;
                        cout<<"your tax is "<<tax<<endl;
					 cout<<"your total is " <<total<<endl;
                        seatingLeft=seatingLeft-tickets;  // each time tickets are purchased that number is subtracted from the seating left and it's updated

               }
               else if(tickets > seatingLeft){
                     cout<<"sorry we can not proccese your request." <<endl;


              }
      }
       	cout<<"Thank you for using My Theatre’s Ticketing Program." <<endl;
      return(0);
}




