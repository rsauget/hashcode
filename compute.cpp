#include <vector>
#include <cmath>
#include <iostream>
#include "compute.h"

using namespace std;

const double INF = (1L << 42);

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
*/

typedef pair<int,int> ii;
typedef pair<ii,int> iii;
typedef pair<ii,ii> pii;

double distance(int r1, int c1, int r2, int c2) {
    return sqrt((r1-r2)*(r1-r2) + (c1-c2)*(c1-c2));
}

void compute(int &rows,int &columns,int &nbDrones,int &nbTicks,int &maxLoad,int &nbProducts,int &nbWarehouses,int &nbOrders,vector<int> &weights,vector<Warehouse> &warehouses,vector<Order> &orders, vector<Drone> &drones)
{
    for(int turn = 0; turn < nbTicks; turn++) {
        //cerr << turn << endl;
        
        //find an objective for all free drones
        for(int d=0; d<drones.size(); ++d) {
            if(drones[d].turnFree < turn)
                continue;

            double minDist = INF;
            pii minMove;

            //TODO : take multiples products
            for(int o=0;o<orders.size();++o) {
                if(orders[o].nbProducts==0)
                    continue;
                for(int p=0;p<orders[o].products.size();++p) {
                    if(orders[o].products[p].second==0)
                        continue;
                    int nbOrderProducts = orders[o].products[p].second;
                    for(int w=0;w<warehouses.size();++w) {
                        if(warehouses[w].products[orders[o].products[p].first] == 0)
                            continue;
                        double productDistance = distance(orders[o].row, orders[o].column, warehouses[w].row, warehouses[w].column);
                        double droneToWare = distance(drones[d].row, drones[d].column, warehouses[w].row, warehouses[w].column);
                        double dist = productDistance + droneToWare;

                        if(dist<minDist)
                        {
                            minDist = dist;
                            minMove.first.first = w ;
                            minMove.first.second = o;
                            minMove.second.first = p;
                            minMove.second.second = min(warehouses[w].products[orders[o].products[p].first], nbOrderProducts);
                            int pd = maxLoad/weights[orders[o].products[p].first];
                            minMove.second.second = min(minMove.second.second, pd);
                        }
                    }
                }
            }

            if(minDist < INF) {
                //choose best move and update drone
                drones[d].turnFree += ceil(minDist) + 2;
                int w = minMove.first.first;
                int o = minMove.first.second;
                int x = minMove.second.first;
                int y = minMove.second.second;
                int p = orders[o].products[x].first;
                drones[d].row = orders[o].row;
                drones[d].column = orders[o].column;

                //update warehouse
                warehouses[w].products[p]-=y;
                orders[o].products[x].second-=y;

                //update order
                orders[o].nbProducts-=y;
                orders[o].turnDone = drones[d].turnFree;

                //write command for output
                drones[d].commands.push_back(toString(d) + " L " + toString(w)  + " " + toString(p) + " "+ toString(y));
                drones[d].commands.push_back(toString(d) + " D " + toString(o) + " " + toString(p) + " "+toString(y));
            }
        }
    }
}