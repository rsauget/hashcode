#include <vector>
#include "compute.h"
using namespace std;

const double INF = (1L << 42);

/*
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

double distance(int r1, int c1, int r2, int c2) {
    double distance = sqrt((r1-r2)*(r1-r2) + (c1-c2)*(c1-c2));
}

void compute(int &rows,int &columns,int &nbDrones,int &nbTicks,int &maxLoad,int &nbProducts,int &nbWarehouses,int &nbOrders,vector<int> &weights,vector<Warehouse> &warehouses,vector<Order> &orders, vector<Drone> &drones)
{
    for(int turn = 0; turn < 400; turn++) {
        cout << turn << endl;
        
        //find an objective for all free drones
        for(int d=0; d<drones.size(); ++d) {
            if(drones[d].turnFree < turn)
                continue;

            double minDist = INF;
            iii minMove;

            //TODO : take multiples products
            for(int o=0;o<orders.size();++o) {
                for(int p=0;p<orders[o].products.size();++p) {
                    for(int w=0;w<warehouses.size();++w) {
                        if(warehouses[w].products[p] == 0)
                            continue;
                        double productDistance = distance(orders[o].row, orders[o].column, warehouses[w].row, warehouses[w].column);
                        double droneToWare = distance(drones[d].row, drones[d].column, warehouses[w].row, warehouses[w].column);
                        double dist = productDistance + droneToWare;
                        if(dist<minDist)
                        {
                            minDist = dist;
                            minMove.first.first = w ;
                            minMove.first.second = o;
                            minMove.second = p;
                        }
                    }
                }
            }

            if(minDist < INF) {
                //choose best move and update drone
                drones[d].turnFree += ceil(minDist) + 2;
                int w = minMove.first.first;
                int o = minMove.first.second;
                int p = minMove.second;
                drones[d].row = orders[o].row;
                drones[d].column = orders[o].column;

                //update warehouse
                warehouses[w].products[p]--;

                //update order
                for(int p2=0;p2<orders[o].products.size();++p2) {
                    if(p == orders[o].products[p2].first) {
                        orders[o].products[p2].second--;
                    }
                }
                orders[o].nbProducts--;

                //write command for output
                drones[d].commands.push_back(toString(d) + " L " + toString(w)  + " " + toString(p) + " 1");
                drones[d].commands.push_back(toString(d) + " D " + toString(o) + " " + toString(p) + " 1");
            }
        }
    }
}