#include "Complex.h"
#include <iostream>

using namespace std;

void enterNumber(Complex& number){
	int choice;
	cout<< "Enter Cartisian(1) or polar(2) complex number? "<<endl;
	cin>>choice;

		if (choice == 1){
		double tempR;
		double tempI;

		cout<< "Enter x value of complex number ( x + yi ): "<<endl;
		cin >> tempR;
		cin.ignore();
		number.set_real(tempR);
		cout<< "Enter y value of complex number ( x + yi ): "<<endl;
		cin >> tempI;
		cin.ignore();
		number.set_imaginary(tempI);


		}
		else{

		double tempRad;
		float tempA;

		cout<< "Enter Radius: "<<endl;
		cin >> tempRad;
		cin.ignore();		
		cout<< "Enter Angle (Deg): "<<endl;
		cin >> tempA;
		cin.ignore();	

		number = Complex(tempRad, tempA);
		};

};


bool performOp(Complex& number, Complex& second_number){
	cout<< "what operation would you like to perform? "<<endl;
	cout<< "1: +	2: -	3: *	4: /	5: ==	6: Show Polar Coordinates"<<endl;

	int operation;
	cin >> operation;
	double scalar;
	switch (operation) {
	case 1:
		enterNumber(second_number);
		//add
		number + second_number;
		break;
	case 2:
		enterNumber(second_number);
		//sub
		number - second_number;
		break;
	case 3:
		cout << "Enter Scalar: ";
		scalar;
		cin >> scalar;
		//mult Scalar and complex
		number * scalar;
		break;
	case 4:
		cout << "Enter Scalar: ";
		scalar;
		cin >> scalar;
				//divide Scalar and complex
		number / scalar;
		break;
	case 5: 
		enterNumber(second_number);
		//==
		if (number == second_number) {
			cout << "They are the same!" << endl;
		}
		else {
			cout << "They are different" << endl;
		}
		return true;
		break;
	case 6:
		cout << "Answer: " << number.string_polar() <<endl;
		return true;
	} // End switch case
	
return false;
}


int main(){
	int choice;
	int operation;
	Complex first_number(2.2, float(2));
	Complex second_number(3.4, double(11));
	int cont = 1;

	while(cont == 1){
		enterNumber(first_number);
		if (!performOp(first_number, second_number)) {
			cout << "Answer: " << first_number.String() << endl;

			cout << endl;
		}
		cout << "Continue? yes(1) no(2): " << endl;
		cin >> cont;
		
	}

	

	
	

	



}