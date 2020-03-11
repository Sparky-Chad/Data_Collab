#ifndef PART_H
#define PART_H
#include <string>
#include "date.h"
using namespace std;



class part
{

public:
	part(int sku, string d, double p, string uom)
	{
		SKU = sku;
		Description = d;
		Price = p;
		UOM = uom;
		QuantityOnHand = 0;
		LeadTime = 5;
	}
	part(int sku, string d, double p, string uom, int Q)
	{
		SKU = sku;
		Description = d;
		Price = p;
		UOM = uom;
		QuantityOnHand = Q;
		LeadTime = 0;
	}

	string GetPartInfo();

	int GetPrice();

	bool InStock();

	bool Available(date);

	friend bool operator>(part p1, part p2)
	{
		return (p1.SKU > p2.SKU);
	}
	friend bool operator<(part p1, part p2)
	{
		return (p1.SKU < p2.SKU);
	}
	friend bool operator==(part p1, part p2)
	{
		return (p1.SKU == p2.SKU);
	}

private:
	int SKU;
	string Description;
	double Price;
	string UOM;
	int QuantityOnHand;
	int LeadTime;
};



#endif