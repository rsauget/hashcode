#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "io.h"
#include "types.h"

using namespace std;

string toString(int i)
{
	ostringstream oss;
	oss<<i;
	return oss.str();
}

void input(int &rows,int &columns,int &nbDrones,int &nbTicks,int &maxLoad,int &nbProducts,int &nbWarehouses,int &nbOrders,vector<int> &weights,vector<Warehouse> &warehouses,vector<Order> &orders)
{
	cin >> rows >> columns >> nbDrones >> nbTicks >> maxLoad;

	cin >> nbProducts;
	weights.resize(nbProducts);
	for(int i=0;i<nbProducts;i++)
	{
		cin >> weights[i];
	}
	cin >> nbWarehouses;
	warehouses.resize(nbWarehouses);
	for(int i=0;i<nbWarehouses;i++)
	{
		cin >> warehouses[i].row >> warehouses[i].column;
		warehouses[i].products.resize(nbProducts);
		for(int j=0;j<nbProducts;j++)
		{
			cin >> warehouses[i].products[j];
		}
	}

	cin >> nbOrders;
	orders.resize(nbOrders);
	int pid;
	for(int i=0;i<nbOrders;i++)
	{
		cin >> orders[i].row >> orders[i].column;
		cin >> orders[i].nbProducts;
		orders[i].products.resize(orders[i].nbProducts);
		int items[nbProducts];
		for(int j=0;j<nbProducts;j++)
		{
			items[i] = 0;
		}
		for(int j=0;j<orders[i].nbProducts;j++)
		{
			cin >> pid;
			items[pid]++;
		}
		for(int j=0;j<nbProducts;j++)
		{
			if(items[j]!=0)
			{
				orders[i].products.push_back(make_pair(j,items[j]));
			}
		}
	}
}

void output(vector<vector<int> > &t, int &n, int &m, int &s)
{
	ofstream out("out/" + toString(s) + "-" + toString(time(0)));
	out << "hello" << endl;
	out.close();
}
