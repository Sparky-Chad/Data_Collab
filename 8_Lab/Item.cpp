#include "Item.h"
#include <string>
using namespace std;





//string GetPartInfo();

string part::GetPartInfo(){
	char sku = static_cast<char>(SKU);
	string temp = "Part Number: " + sku;
	temp =" Description: "+ Description;
	return temp;
}

int part::GetPrice(){
	return Price;
}

bool part::InStock(){
	if(QuantityOnHand == 0){
		return false;
	};
	return true;
}

bool Available(date )