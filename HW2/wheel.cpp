

#include "wheel.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int wheel::spin() {
	return int((rand() % (high-low)) + low);
}



bool wheel::house_spin(int numTobeat) {
	int svalue = spin();
	cout << "House spins a " << svalue << endl;
	if (svalue>numTobeat){
		return 1;
	};
	return 0;
}


