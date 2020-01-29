#pragma once
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;




class Player {

	public:
		
		Player(string);
		

		void setName(string);
		string getName() {return name;}

		int getshotsTaken();
		void setshotsTaken(int);

		int getshotsMade();
		void setshotsMade(int);

		int getpassesAttempted();
		void setpassesAttempted(int);

		int getpassesMade();
		void setpassesMade(int);

		bool passBall();

		int takeShot(int);

		void getStats();






	private:
		string name;
		double shotsTaken;
		double shotsMade;
		double passesAttempted;
		double passesMade;

};
