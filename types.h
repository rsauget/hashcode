#ifndef TYPES_H
#define TYPES_H
#include <vector>
#include <string>
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
	int turnDone;
	vector<pair<int,int> > products;
};
struct Drone
{
  int row;
  int column;
  int turnFree;
  vector<pair<int,int> > products;
  vector<string> commands;
};
#endif