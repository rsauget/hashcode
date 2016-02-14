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

void input(int &rows,int &columns,int &nbDrones,int &nbTicks,int &maxLoad,int &nbProducts,int &nbWarehouses,int &nbOrders,vector<int> &weights,vector<Warehouse> &warehouses,vector<Order> &orders, vector<Drone> &drones, string fileName)
{
	ifstream in(fileName);
	in >> rows >> columns >> nbDrones >> nbTicks >> maxLoad;

	in >> nbProducts;
	weights.resize(nbProducts);
	for(int i=0;i<nbProducts;i++)
	{
		in >> weights[i];
	}

	in >> nbWarehouses;
	warehouses.resize(nbWarehouses);
	for(int i=0;i<nbWarehouses;i++)
	{
		in >> warehouses[i].row >> warehouses[i].column;
		warehouses[i].products.resize(nbProducts);
		for(int j=0;j<nbProducts;j++)
		{
			in >> warehouses[i].products[j];
		}
	}

	in >> nbOrders;
	orders.resize(nbOrders);
	int pid;
	for(int i=0;i<nbOrders;i++)
	{
		in >> orders[i].row >> orders[i].column;
		in >> orders[i].nbProducts;
		int items[nbProducts];
		for(int j=0;j<nbProducts;j++)
		{
			items[j] = 0;
		}
		for(int j=0;j<orders[i].nbProducts;j++)
		{
			in >> pid;
			items[pid]++;
		}
		int cnt=0;
		for(int i=0;i<nbProducts;i++)
			if(items[i]) cnt+=items[i];
		orders[i].nbProducts = cnt;
		for(int j=0;j<nbProducts;j++)
		{
			if(items[j]>0)
			{
				orders[i].products.push_back(make_pair(j,items[j]));
			}
		}
		orders[i].turnDone = -1;
	}

	drones.resize(nbDrones);
	for(int i=0;i<nbDrones;i++)
	{
		drones[i].row = warehouses[0].row;
		drones[i].column = warehouses[0].column;
		drones[i].turnFree = 0;
	}
	in.close();
}

void output(int &nbDrones, vector<Drone> &drones, int& score, string fileName)
{
	string outFileName = "out/" + fileName.substr(0,fileName.find_last_of(".")) + "-" + toString(score) + "-" + toString(time(0));
	ofstream out(outFileName);
	int nbCommands = 0;
	for(int i=0;i<nbDrones;i++)
	{
		nbCommands += drones[i].commands.size();
	}
	out << nbCommands << "\n";
	for(int i=0;i<nbDrones;i++)
	{
		for(int j=0;j<drones[i].commands.size();j++)
		{
			out << drones[i].commands[j] << "\n";
		}
	}
	out.close();
	cerr << "written " << outFileName << endl;
}