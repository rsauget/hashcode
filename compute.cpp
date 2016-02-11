#include <vector>
#include <cmath>
#include "compute.h"
using namespace std;

struct SubOrder
{
    int warehouse;
    int order;
    int product;
};

double distance(int r1, int c1, int r2, int c2) {
    return sqrt((r1-r2)*(r1-r2) + (c1-c2)*(c1-c2));
}

int firstFreeDrone(int &nbDrones, vector<Drone> &drones)
{
    int droneNo;
    int minTurnFree = 1000000;
    for(int i=0;i<nbDrones;i++)
    {
        if(drones[i].turnFree < minTurnFree)
        {
            minTurnFree = drones[i].turnFree;
            droneNo = i;
        }
    }
    return droneNo;
}

int nearestWarehouse(int &nbWarehouses, vector<Warehouse> &warehouses, int row, int column)
{
    int wareHouseNo;
    double minDistance = 1000000;
    for(int i=0;i<nbWarehouses;i++)
    {
        double newDistance = distance(row,column,warehouses[i].row,warehouses[i].column);
        if(newDistance < minDistance)
        {
            minDistance = newDistance;
            wareHouseNo = i;
        }
    }
    return wareHouseNo;
}

int findProduct(int &nbWarehouses, vector<Warehouse> &warehouses, int product)
{
    for(int i=0;i<nbWarehouses;i++)
    {
        //On cherche le produit dans l'entrepot.
        if (warehouses[i].products[product] > 0)
        {
            return i;
        }
    }
    return -1;
}

vector<SubOrder> computeSubOrder(int &nbOrders, vector<Order> &orders, int &nbWarehouses, vector<Warehouse> &warehouses)
{
    vector<SubOrder> suborders;

    //Pour chaque commande.
    for (int i = 0;i < nbOrders;i++)
    {
        //Pour chaque produit de la commande.
        for (int j = 0;j < orders[i].products.size();j++)
        {
            if (orders[i].products[j].second > 0)
            {
                //On genere une sous commande.
                SubOrder suborder;

                suborder.product = orders[i].products[j].first;
                suborder.warehouse = findProduct(nbWarehouses, warehouses, suborder.product);
                suborder.order = i;

                suborders.push_back(suborder);

                //On met a jour l'order et le warehouse.
                orders[i].products[j].second--;
            }
        }
    }

    return suborders;
}

void compute(int &rows,int &columns,int &nbDrones,int &nbTicks,int &maxLoad,int &nbProducts,int &nbWarehouses,int &nbOrders,vector<int> &weights,vector<Warehouse> &warehouses,vector<Order> &orders, vector<Drone> &drones)
{
    

    int turn = 0;
    while(turn < nbTicks)
    {
        //On repere le drone qui est pret en premier.
        int drone = firstFreeDrone(nbDrones, drones);
        turn = drones[drone].turnFree;
        //On repere la commande la plus proche.

        //On envoie le max de produits

        //On retourne a l'entrepot le plus proche.

    }
}
