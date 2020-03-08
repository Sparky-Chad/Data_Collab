//gotcha, sorry about that
//thanks
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "wheel.h"
#include "Player.h"
#include "Hard_Wheel.h"

using namespace std;


int main(){
    srand(static_cast <unsigned> (time(0)));
	int player_cash;
	bool play = 1;
	int wheel_size;
    int wheel_min = 0;
	bool hard_mode = 0;
	double bet;
	int choice;

	cout << "Welcome to Roulette, How much cash would you like to play with? (min bet per roll is 10)" << endl;
	cin >> player_cash;
	cin.ignore();
	cout << "How big of a wheel do you want to play with? Enter the highest number (between 6 and 20)" << endl;
	cin >> wheel_size;
	cout << "Easy(0) or Hard(1) mode?" << endl;
	cin >> hard_mode;

	Player myPlayer (player_cash,hard_mode,0,wheel_size);

	
	while (myPlayer.current_money() > 0 && play == 1)
	{
		bet = 0;
        // pass bounds into player class, it sets up the wheels
		while(bet > myPlayer.current_money() || bet < 10) {
            cout << "You have $" << myPlayer.current_money() << ", how much would you like to bet?" << endl;
            cout << "Min bet amount, $10\n";
            cin >> bet;
            cin.ignore();
        }
		//handle if they bet more than they have or to little
		cout << "Spinning..." <<endl;

		cout << "You got a " << myPlayer.Player_Spin() << endl;

		
        bool modulate = false;
        do {
            cout<< "You may choose to halve(0), stay(1), double(2) your bet:   "<<endl;
            cin >> choice;
            if (choice == 2 && bet *2 > myPlayer.current_money()) {
                modulate = true;
            }else {
                modulate = false;
            }
        } while(modulate);


		
		

		double earnings = myPlayer.Challenge_House(bet, choice);

		if(earnings > 0) {
            cout << "\n\nGreat you beat the house!\n";
        }
        else if(earnings == 0) {
            cout << "\n\nA good safe bet, you broke even\n";
        }
        else if(earnings < 0) {
            cout << "\n\nYou lost money, though you could always win it back...\n";
        }

        printf("Current Money is: $%05.2f\n\n", myPlayer.current_money());

        cout << "Would you like to play again?(y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();
        if(choice == 'y' || choice == 'Y') {
            play = 1;
        } else {
            play = 0;
        }
	}
}
