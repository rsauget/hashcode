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
	vector<int> items;
};
struct Order
{
	int row;
	int column;
	vector<pair<int,int> > products;
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

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	input(rows,columns,nbDrones,nbTicks,maxLoad,nbProducts,nbWarehouses,nbOrders,weights,warehouses,orders);
	cout << "done" << endl;
	//draw(t,n,m,zoom);
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