#include "Part.h"
#include <string>
#include <ctime>
#include <chrono>
#include <sstream>
using namespace std;
//string GetPartInfo();
string part::GetPartInfo(){
	ostringstream temp;
	
	temp << "Part Number: " << to_string(SKU) << '\n';
	temp << "Description: " << Description << '\n';
	temp << "Price: $" << Price << '\n';
	return temp.str();
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

bool part::Available(struct tm in)
{

	//First check if there is a supply of the stuck they would like
	if(this->QuantityOnHand > 0)
	{
		return true;
	}
	
	// Now build up whether the users date falls within when more
	// of the stock can be ordered

	// Creating a typedef which can convert to days for this operation
	// inspired from: https://www.programming-books.io/essential/cpp/find-number-of-days-between-two-dates-af8b82240915498c8ea5f7d1c77bc831

	typedef chrono::duration<int, ratio_multiply<chrono::hours::period, ratio<24>>::type> day;
	time_t t; 
	time(&t);
	auto today = chrono::system_clock::from_time_t(mktime(localtime(&t)));
	auto todate = chrono::system_clock::from_time_t(mktime(&in));

	day difference = chrono::duration_cast<day>(todate - today);
	// parse the difference between the two times and compare if
	// the days from today is greater than the number of days it takes to 
	// refill the order

	day cmp = chrono::duration_cast<day>(chrono::duration<int, ratio<1, 86400>>{(LeadTime)});

	if(difference < cmp)
	{
		return false;
	}	
	else 
	{
		return true;
	}
}