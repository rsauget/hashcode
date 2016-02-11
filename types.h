#ifndef TYPES_H
#define TYPES_H
#include <vector>
using namespace std;
struct Warehouse
{
	int row;
	int column;
	vector<int> products;
};
struct Order
{
	int row;
	int column;
	int nbProducts;
	vector<pair<int,int> > products;
};
#endif