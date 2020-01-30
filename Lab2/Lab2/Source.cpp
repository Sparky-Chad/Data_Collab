#include <iostream>
#include <iomanip>
#include <string>
#include "Player.h"
#include <cstdlib>
using namespace std;

/*

	Source.cpp
	Creates and manages the basketball game and uses the player class. 

	Created Cooperatively by Chad Lape and Colton Murra
*/


void stats();
void score();

//Declares start of players turn
void players_turn_start();
//players turn random player
void players_possesion();
//players turn
void players_possesion(int);
//Ends players turn and gives possesion to ai
void end_players_turn();

// for player stat shoot
void shoot(int);

// accepts as ai = false, stat, and attempted score
void shoot();

// continues possession with another player
void pass(int);


int user_possesions = 0;
int ai_possesions = 0;
// returns possesions left
int user_possesions_left() {return 20 - user_possesions;}
int ai_possesions_left() { return 20 - ai_possesions;}

string names[] = { "mike", "lebron", "kobe", "colton", "james" };


//Scores
int user_score = 0;
int ai_score = 0;

// input for player is (name);
Player mike(names[0]);
Player lebron(names[1]);
Player kobe(names[2]);
Player colton(names[3]);
Player james(names[4]);

Player Players[] = { mike,lebron,kobe,colton,james };

int main() {
	
	cout << "Beginning game"<<endl;
	while (user_possesions < 20) {
		
		//begins the turn and deals with possesions
		players_turn_start();
		//ends the turn and begins the ai turn
		end_players_turn();
		
	}
	cout << "**Game is OVER**\n\n";
	cout << "Final score:\n";
	score(); 

	return 0;
}

//start Players turn
void players_turn_start() {

	cout << "Begining round, adding a possesion\n";
	user_possesions++;
	players_possesion();

}



void players_possesion() {

	int playerSelect = (rand() % 5);
	players_possesion(playerSelect);
}

void players_possesion(int playerSelect) {
	int Choice;
	cout << "\n\nUser Possesions left: " << user_possesions_left() << "\nAI Possesions left: " << ai_possesions_left() <<'\n';
	cout << "\n\nCurrent Ball Carrier: "  << Players[playerSelect].getName() << endl<< endl; 
	cout << "1: shoot	2: pass		3: stats	4: Score" << endl;
	cin >> Choice;

	switch (Choice)
	{
		case 1:
			shoot(playerSelect);
			break;
		case 2:
			pass(playerSelect);
			break;
		case 3:
			stats();
			players_possesion(playerSelect);
			break;
		case 4:
			score();
			players_possesion(playerSelect);
			break;
			
				
	}

}

//Ends the players turn and transitions to the ai
void end_players_turn() {
	ai_possesions++;
	shoot();
}

//Shoot Definition for player

void shoot(int i) {

	//handle point attempt amount
	int amount;

	while(true) {
		cout << "Score amount to attempt for (1, 2, 3): ";
		cin >> amount;
		if(amount > 0 && amount < 4) break;
		cin.ignore();
	}

	//Output the attempt
	if(amount == 1) {
		cout << Players[i].getName() << " attempting to score for " << amount << " point" << endl;
	}
	else {
		cout << Players[i].getName() << " attempting to score for " << amount << " points" << endl;
	}


	int temp = Players[i].takeShot(amount);

	if(temp == 0) {
		cout << Players[i].getName() << " missed, the other team has possesion" << endl;
		shoot();
	}
	else {
		cout << Players[i].getName() << " Scored!\n";
		user_score += temp;
	}
}


// Handle the AI shooting
void shoot() {

	//possible score attempt
	int attempt = rand() % 3 + 1;
	
	cout << "Other team shooting for " << attempt << " points" << endl;
	if((rand() % 101) > 60) {
		cout << "Other team scored!\n";
		ai_score += attempt;
	}
	else {
		cout << "They Missed!" << endl;
		if((rand() % 101) > 50) 
		{
			//ai recovered it
			cout << "They recovered the ball" << endl;
			shoot();
			return;
		}
		else 
		{
			// goes to players possesion
			int player = rand() % 5;
			cout << Players[player].getName() << " recovered the ball! Your Turn:\n";
			players_possesion(player);
		}
	}
	
}




void stats() {
	int i;
	for (i = 0; i < 4; i++) {
		Players[i].getStats();
	}
}

void score() {

	cout << "YOU: " << user_score << "\tOPPONENT: " << ai_score<<endl;

}

void pass(int currentPlayer) {

	int nextPlayer = currentPlayer;
	while (nextPlayer == currentPlayer) {
		nextPlayer = (rand() % 5);
	}
	cout << Players[currentPlayer].getName() << " passes to " << Players[nextPlayer].getName() << "!\n";
	if (Players[currentPlayer].passBall()) {
		cout << " Pass Succeeded" << endl;
		players_possesion(nextPlayer);
	}
	else {
		cout << "The other team stole the ball!" << endl;
		shoot();
	}

}







