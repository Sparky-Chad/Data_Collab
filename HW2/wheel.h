#ifndef WHEEL_H
#define WHEEL_H

using namespace std;




class wheel
{
public:
	wheel() {
		low = 1;
		high = 10;
	};

	wheel(int min, int max) {
		this->low = min;
		this->high = max;
	};

	int spin();
	virtual bool house_spin(int competing);
	
	// Returns the highest bound
	int get_high() { return high; }
	// Returns the lowest bound
	int get_low() { return low; }

protected:
	int low;
	int high;	   	  

};


#endif