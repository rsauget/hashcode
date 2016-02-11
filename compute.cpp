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

            double maxScore = -1;
            pair< vector<pair<int,int>>, int> bestMove;
            int bestOrder = -1;

            //TODO : take multiples products
            for(int o=0;o<orders.size();++o) {
                if(orders[o].nbProducts==0)
                    continue;
                double productDistance, droneToWare, dist;
                vector<pii> productsToBring;

                double maxScoreWare = -1;
                int bestWare = -1;

                for(int w=0;w<warehouses.size();++w) {
                    double orderDistance = distance(orders[o].row, orders[o].column, warehouses[w].row, warehouses[w].column);
                    double scoreWare = 0;
                    for(int p=0;p<orders[o].products.size();++p) {
                        int nbOrderProducts = orders[o].products[p].second;
                        if(warehouses[w].products[orders[o].products[p].first] == 0)
                            continue;
                        scoreWare += min(warehouses[w].products[orders[o].products[p].first], nbOrderProducts);
                    }
                    scoreWare /= orderDistance;
                    if(scoreWare > maxScoreWare) {
                        maxScoreWare = scoreWare;
                        bestWare = w;
                    }
                }

                for(int p=0;p<orders[o].products.size();++p) {
                    if(orders[o].products[p].second==0)
                        continue;
                    if(warehouses[bestWare].products[orders[o].products[p].first] == 0)
                            continue;

                    int nbOrderProducts = orders[o].products[p].second;
                    double orderDistance = distance(orders[o].row, orders[o].column, warehouses[bestWare].row, warehouses[bestWare].column);

                    productsToBring.push_back(make_pair(
                        make_pair(p, bestWare),
                        make_pair(min(warehouses[bestWare].products[orders[o].products[p].first], nbOrderProducts), orderDistance)
                        ));
                }

                double currentWeight = 0;
                while(true) {
                    cerr << d << endl;
                    double maxScore = 0;
                    int bestProduct = -1;
                    for(int pindex = 0; pindex<productsToBring.size(); pindex++) {
                        auto p = productsToBring[pindex];
                        double score = p.second.first;
                        int pd = (maxLoad - currentWeight)/weights[orders[o].products[p.first.first].first];
                        score = min((int)score, pd);

                        if(weights[p.first.first]*p.second.first + currentWeight > maxLoad) {
                            score = -1;
                        }
                        if(score > maxScore) {
                            bestProduct = pindex;
                            maxScore = score;
                        }
                    }
                    if(bestProduct==-1)
                        break;
                    drones[d].products.push_back(make_pair(productsToBring[bestProduct].first.first, productsToBring[bestProduct].second.first));
                    currentWeight += maxScore * weights[orders[o].products[productsToBring[bestProduct].first.first].first];
               }

                if(drones[d].products.size() > maxScore)
                {
                    maxScore = drones[d].products.size();
                    bestMove = make_pair(drones[d].products, bestWare);
                    bestOrder = o;
                }
                cerr << "yo" << endl;
            }

            if(maxScore > 0) {
                cerr << "hello" << endl;
                //choose best move and update drone
                double droneToWare = distance(drones[d].row, drones[d].column, warehouses[bestMove.second].row, warehouses[bestMove.second].column);
                double wareToOrder = distance(orders[bestOrder].row, orders[bestOrder].column, warehouses[bestMove.second].row, warehouses[bestMove.second].column);
                drones[d].turnFree += ceil(droneToWare+wareToOrder) + 2*bestMove.first.size();
                drones[d].row = orders[bestOrder].row;
                drones[d].column = orders[bestOrder].column;

                //update warehouse
                for(auto pindex : drones[d].products) {
                    auto p = orders[bestOrder].products[pindex.first];
                    warehouses[bestMove.second].products[p.first] -= p.second;
                    for(int p2=0; p2<orders[bestOrder].products.size(); ++p2) {
                        if(orders[bestOrder].products[p2].first == p.first)
                            orders[bestOrder].products[p2].second -= p.second;
                    }
                }

                //update order
                orders[bestOrder].nbProducts-=bestMove.first.size();
                orders[bestOrder].turnDone = drones[d].turnFree;

                //write command for output
                for(auto pindex : drones[d].products) {
                    auto p = orders[bestOrder].products[pindex.first];
                    drones[d].commands.push_back(toString(d) + " L " + toString(bestMove.second)  + " " + toString(p.first) + " "+ toString(p.second));
                }
                for(auto pindex : drones[d].products) {
                    auto p = orders[bestOrder].products[pindex.first];
                    drones[d].commands.push_back(toString(d) + " D " + toString(bestOrder) + " " + toString(p.first) + " "+toString(p.second));
                }
            }
        }
    }
}