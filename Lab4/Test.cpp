//Tester methods for the created classes
// Chad and Colon

// Includes
#include "Movie.h"
#include "Show.h"
#include "TV_Show.h"

// For in/out
#include <iostream>
// Strings
#include <string>

// Season Episode array to create

string SE[3][5]{
{"Phantom Menace", "2nd One Bites the Dust", "Another one down", "And Another one Down", "Oh No" },
{"Attack of the copyright", "Revenge of the CopyRight", "A New Hope", "2nd 4th", "Final Countdown"},
{"Badadoodoo", "Badadoodoo: Electric Boogaloo", "Counting fight", "Hello World", "Final Ever"}
};
void fill();

using namespace std;

//main function
int main() {
	bool again = true;
	cout << "Welcome to the lab 4 tester with testing shows, movies, and tv shows" << endl;
	do {
		//Create pointers to null of types
		Show* s = nullptr;
		Movie* m = nullptr;
		tvShow* t = nullptr;
		int choice = 0;
		// Get the users choice
		cout << "Will output details and the play function" << endl;
		cout << "1: Instance of Show" << endl << "2: Instance of Movie" << endl \
			<< "3: Instance of TV Show" << endl << "4: Instance of a Movie declared as a Show" \
			<< endl << "5: Instance of TV Show declared as a Show" << endl << endl;
		cout << "Choice: ";
		cin >> choice;
		cin.ignore();

		// variables for the switch
		string tempt, tempd;
		double tempr;
		// Decide what happens
		switch (choice) {
		case 1:
			//Make new show
			cout << "Title of Show: ";
			getline(cin, tempt);
			cout << "Description of show: ";
			getline(cin, tempd);
			cout << "Result of play and print_details" << endl << endl << endl; 
			s = new Show(tempt, tempd);
			//Now use the show values
			s->print_details();
			s->play();

			//delete show to prevent memory leak
			delete s;
			break;
		case 2:
			// Create instance of Movie
			cout << "Title of Movie: ";
			getline(cin, tempt);
			cout << "Description of Movie: ";
			getline(cin, tempd);
			cout << "Rating of Movie: ";
			cin >> tempr;
			cin.ignore();
			m = new Movie(tempr, tempt, tempd);
			// Print functions
			cout << "Print Movie play and print_details" << endl << endl;
			m->print_details();
			m->play();
			// deal with memory
			delete m;
			break;
		case 3: 
			// Create instance of tvShow
			cout << "Title of TV Show: ";
			getline(cin, tempt);
			cout << "Description of TV Show: ";
			getline(cin, tempd);
			cout << "Premade show of 3 seasons and 5 episodes is made";
			t = new tvShow(SE, tempt, tempd);
			cout << "Result of play and print_details" << endl << endl;
			// Send application 
			t->print_details();
			t->play();
			// Caress the Memory
			delete t;
			break;
		case 4:
			// Will Create and instance of Movie as a Show pointer
			cout << "Title of Movie: ";
			getline(cin, tempt);
			cout << "Description of Movie: ";
			getline(cin, tempd);
			cout << "Rating of Movie: ";
			cin >> tempr;
			cin.ignore();
			s = new Movie(tempr, tempt, tempd);
			// Print Functions
			cout << "Result of play and print_details" << endl << endl << endl; 
			s->print_details();
			s->play();
			delete s;
			break;
		case 5:
			// Will create an instance of tvShow as a Show pointer
			cout << "Title of TV Show: ";
			getline(cin, tempt);
			cout << "Description of TV Show: ";
			getline(cin, tempd);
			cout << "Premade show of 3 seasons and 5 episodes is made";
			cout << "Result of play and print_details" << endl << endl << endl; 
			s = new tvShow(SE, tempt, tempd);
			// Output
			s->print_details();
			s->play();
			// Caress the memory
			delete s;
			break;
		}


		//Do again
		char temp = 'n';
		cout << endl << endl << "Would you like to run again?(y/n): ";
		cin >> temp;
		cin.ignore();
		again = temp == 'y';
	} while (again);
	return 0;
}


//Fills array of Seasons and Episodes
/*
void fill() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			SE[i][j] = "Episode " + (j + 1);
		}
	}
}
*/