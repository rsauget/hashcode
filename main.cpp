#include <iostream>
#include <string>
#include <vector>
#include "io.h"
#include "draw.h"
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
	input(rows,columns,nbDrones,nbTicks,maxLoad,nbProducts,nbWarehouses,nbOrders,weights,warehouses,orders);
	cerr << nbWarehouses << " warehouses" << endl;
	draw(rows,columns,nbWarehouses,warehouses,2);
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
			output(t,n,m,score);
		}
	}
	*/
	return 0;
}