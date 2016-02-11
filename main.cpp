#include <iostream>
#include <string>
#include <vector>
#include "io.h"
//#include "draw.h"
#include "compute.h"
#include "eval.h"
#include "types.h"

using namespace std;

/*
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
struct Drone
{
	int row;
	int column;
	int turnFree;
	vector<pair<int,int> > products;
	vector<string> commands;
};
*/

int rows;
int columns;
int nbDrones;
int nbTicks;
int maxLoad;
int nbProducts;
int nbWarehouses;
int nbOrders;

vector<int> weights;
vector<Warehouse> warehouses;
vector<Order> orders;
vector<Drone> drones;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	input(rows,columns,nbDrones,nbTicks,maxLoad,nbProducts,nbWarehouses,nbOrders,weights,warehouses,orders,drones);
	cerr << rows << "x" << columns << " map" << endl;
	cerr << nbTicks << " ticks" << endl;
	cerr << nbDrones << " drones" << endl;
	cerr << nbProducts << " products" << endl;
	cerr << nbWarehouses << " warehouses" << endl;
	cerr << nbOrders << " orders" << endl;
	//draw(rows,columns,nbWarehouses,warehouses,2);
	compute(rows,columns,nbDrones,nbTicks,maxLoad,nbProducts,nbWarehouses,nbOrders,weights,warehouses,orders,drones);
	output(nbDrones,drones);
	/*
	int best = -1;
	int score;
	while(1)
	{
		compute(t,n,m);
		score = eval(t,n,m);
		if(score > best)
		{
			best = score;
			output(nbDrones,drones);
		}
	}
	*/
	return 0;
}