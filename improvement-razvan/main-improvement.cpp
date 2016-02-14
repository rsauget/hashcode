#include <bits/stdc++.h>
#include <ctgmath>

using namespace std;

const int INF = 1000000;

struct Warehouse
{
    int row;
    int column;
    int nbProducts;
    vector<int> products;
};
struct Order
{
    int row;
    int column;
    int nbProducts;
    int turnDone;
    vector<int> products;
};
struct Drone
{
  int row;
  int column;
  int turnFree;
  vector<string> commands;
};

int rows;
int columns;
int nbDrones;
int nbTurns;
int maxLoad;
int nbProducts;
int nbWarehouses;
int nbOrders;

vector<int> weights;
vector<Warehouse> warehouses;
vector<Order> orders;
vector<Drone> drones;

string toString(int i)
{
    ostringstream oss;
    oss<<i;
    return oss.str();
}

int distance(int r1, int c1, int r2, int c2) {
    return ceil(sqrt((r1-r2)*(r1-r2) + (c1-c2)*(c1-c2)));
}

int min(int a, int b)
{
    return a<b?a:b;
}

void input(int &rows,int &columns,int &nbDrones,int &nbTurns,int &maxLoad,int &nbProducts,int &nbWarehouses,int &nbOrders,vector<int> &weights,vector<Warehouse> &warehouses,vector<Order> &orders, vector<Drone> &drones, string fileName)
{
    ifstream in(fileName);
    in >> rows >> columns >> nbDrones >> nbTurns >> maxLoad;

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
        warehouses[i].nbProducts = 0;
        for(int j=0;j<nbProducts;j++)
        {
            in >> warehouses[i].products[j];
            warehouses[i].nbProducts += warehouses[i].products[j];
        }
    }

    in >> nbOrders;
    orders.resize(nbOrders);
    int pid;
    for(int i=0;i<nbOrders;i++)
    {
        in >> orders[i].row >> orders[i].column;
        in >> orders[i].nbProducts;
        orders[i].products.resize(nbProducts);
        for(int j=0;j<orders[i].nbProducts;j++)
        {
            in >> pid;
            orders[i].products[pid]++;
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

void compute(int &rows,int &columns,int &nbDrones,int &nbTurns,int &maxLoad,int &nbProducts,int &nbWarehouses,int &nbOrders,vector<int> &weights,vector<Warehouse> &warehouses,vector<Order> &orders, vector<Drone> &drones)
{
    for(int turn=0;turn<nbTurns;turn++)
    {
        int alpha=0;
        int used[nbDrones];
        for(int i=0;i<nbDrones;++i)
        {
            if(drones[i].turnFree==turn)
                used[i]=0;
            else used[i]=1;
        }
        while(alpha<nbDrones*2)
        {
            alpha++;
            int chosenDrone = -1;
            int minDistance = INF;
            int chosenWarehouse = -1;
            int chosenOrder = -1;
            int chosenNbProductTypes = -1;
            int chosenWeight = -1;
            int bestScore = INF;
            vector<int> chosenProducts;
            for(int drone=0;drone<nbDrones;drone++)
            {
                //cerr << "drone " << drone << endl;
                // Drone busy, skip
                for(int warehouse=0;warehouse<nbWarehouses;warehouse++)
                {
                    // Empty warehouse
                    if(warehouses[warehouse].nbProducts == 0)
                    {
                        continue;
                    }
                    for(int order=0;order<nbOrders;order++)
                    {
                        // Finished order
                        if(orders[order].nbProducts == 0)
                        {
                            continue;
                        }
                        int weight = 0;
                        // TODO: add weight when more products
                        int newDistance = distance(
                                drones[drone].row,drones[drone].column,
                                warehouses[warehouse].row,warehouses[warehouse].column
                            ) + distance(
                                warehouses[warehouse].row,warehouses[warehouse].column,
                                orders[order].row,orders[order].column
                            );
                        int newNbProductTypes = 0;
                        vector<int> newProducts(nbProducts,0);
                        int pfai=0;
                        for(int product=0;product<nbProducts;product++)
                        {
                            // Product ordered and in stock
                            if(orders[order].products[product] > 0 && warehouses[warehouse].products[product] > 0)
                            {
                                int quantity = min(orders[order].products[product],warehouses[warehouse].products[product]);
                                quantity = min((maxLoad-weight)/weights[product],quantity);
                                if(quantity > 0)
                                {
                                    pfai+=quantity;
                                    newProducts[product] += quantity;
                                    newNbProductTypes++;
                                    weight += newProducts[product] * weights[product];
                                }
                            }
                        }
                        int score = newDistance+2*newNbProductTypes+drones[drone].turnFree;
                        if(orders[order].nbProducts != pfai)
                            score+=1000;
                        if((score < bestScore) && newNbProductTypes > 0)
                        {
                            bestScore=score;
                            chosenWarehouse = warehouse;
                            chosenOrder = order;
                            chosenProducts = vector<int>(newProducts);
                            chosenNbProductTypes = newNbProductTypes;
                            chosenWeight = weight;
                            chosenDrone = drone;
                            minDistance = newDistance;  
                        }
                    }
                }
            }
            if(minDistance == INF)
                break;
            // Drone not full, try to chain orders
            vector<int> newOrders;
            vector<vector<int>> newProducts;
            vector<int> newDistances;
            int drone  = chosenDrone;

            vector<int> warehouseLevel(warehouses[chosenWarehouse].products);
            for(int product=0;product<nbProducts;product++)
            {
                warehouseLevel[product] -= chosenProducts[product];
            }
            int previousOrder = chosenOrder;
            int bestCnt=0;
            while(chosenWeight < maxLoad)
            {
                int newMinDistance = INF;
                int newChosenOrder = -1;
                int newChosenWeight = -1;
                int newBestScore = INF;
                vector<int> newChosenProducts(nbProducts,0);
                for(int order=0;order<nbOrders;order++)
                {
                    if(orders[order].nbProducts == 0 || order == chosenOrder || find(newOrders.begin(),newOrders.end(),order) != newOrders.end())
                    {
                        continue;
                    }
                    int weight = chosenWeight;
                    int newDistance = distance(
                        orders[previousOrder].row,orders[previousOrder].column,
                        orders[order].row,orders[order].column
                        );
                    vector<int> newProducts(nbProducts,0);
                    int pfai=0;
                    int cnt=0;
                    for(int product=0;product<nbProducts;product++)
                    {
                        if(orders[order].products[product] > 0 && warehouseLevel[product] > 0)
                        {
                            int quantity = min(orders[order].products[product],warehouseLevel[product]);
                            quantity = min((maxLoad-weight)/weights[product],quantity);
                            if(quantity > 0)
                            {
                                pfai+=quantity;
                                cnt++;
                                newProducts[product] += quantity;
                                weight += newProducts[product] * weights[product];
                            }
                        }
                    }
                    int score = newDistance+2*cnt;
                    if(orders[order].nbProducts != pfai)
                        score+=50;
                    if((score < newBestScore) && weight > chosenWeight)
                    {
                        newBestScore=score;
                        newChosenOrder = order;
                        newChosenProducts = vector<int>(newProducts);
                        newChosenWeight = weight;
                        newMinDistance = newDistance; 
                        bestCnt=cnt;  
                    }
                }
                if(newMinDistance == INF)
                    break;
                newOrders.push_back(newChosenOrder);
                //cerr << "added order " << newChosenOrder << " after " << chosenOrder << endl;
                newProducts.push_back(vector<int>(newChosenProducts));
                newDistances.push_back(newMinDistance);
                for(int product=0;product<nbProducts;product++)
                {
                    warehouseLevel[product] -= newChosenProducts[product];
                }
                //cerr << "add weight " << chosenWeight << " -> " << newChosenWeight << endl;
                chosenWeight = newChosenWeight;
                previousOrder = newChosenOrder;
            }
            // Load everything
            vector<int> totalQuantities(chosenProducts);
            for(int product=0;product<nbProducts;product++)
            {
                orders[chosenOrder].products[product] -= chosenProducts[product];
                orders[chosenOrder].nbProducts -= chosenProducts[product];
                for(int order=0;order<newOrders.size();order++)
                {
                    totalQuantities[product] += newProducts[order][product];
                    orders[newOrders[order]].products[product] -= newProducts[order][product];
                    orders[newOrders[order]].nbProducts -= newProducts[order][product];
                }
            }
            for(int product=0;product<nbProducts;product++)
            {
                if(totalQuantities[product] > 0)
                {
                    warehouses[chosenWarehouse].products[product] -= totalQuantities[product];
                    warehouses[chosenWarehouse].nbProducts -= totalQuantities[product];
                    drones[drone].commands.push_back(
                        toString(drone) + " L " +
                        toString(chosenWarehouse) +
                        " " + toString(product) +
                        " " + toString(totalQuantities[product])
                        );
                }
            }
            drones[drone].turnFree += minDistance;
            for(int product=0;product<nbProducts;product++)
            {
                if(totalQuantities[product] > 0)
                {
                    drones[drone].turnFree++;//LOAD
                }
                if(chosenProducts[product] > 0)
                {
                    drones[drone].turnFree++;//DELIVER 1st
                    drones[drone].commands.push_back(
                        toString(drone) + " D " +
                        toString(chosenOrder) +
                        " " + toString(product) +
                        " " + toString(chosenProducts[product])
                        );
                }
            }
            if(orders[chosenOrder].nbProducts == 0)
            {
                orders[chosenOrder].turnDone = drones[drone].turnFree;
            }
            for(int order=0;order<newOrders.size();order++)
            {
                drones[drone].turnFree += newDistances[order];
                for(int product=0;product<nbProducts;product++)
                {
                    if(newProducts[order][product] > 0)
                    {
                        drones[drone].turnFree++;//DELIVER next
                        drones[drone].commands.push_back(
                            toString(drone) + " D " +
                            toString(newOrders[order]) +
                            " " + toString(product) +
                            " " + toString(newProducts[order][product])
                            );
                    }
                }
                if(orders[newOrders[order]].nbProducts == 0)
                {
                    orders[newOrders[order]].turnDone = drones[drone].turnFree;
                }
            }
        }
        int productsLeft=0;
        for(int i=0;i<nbOrders;++i)
        {
            for(int j=0;j<orders[i].products.size();++j)
            {
                productsLeft+=orders[i].products[j];
            }
        }
        if(productsLeft==0)
            break;
        cerr << "turn " << turn <<"   "<<productsLeft<<"  prodcuts left" << endl;
        for(int i=0;i<nbDrones;++i)
        {
            if(!used[i])
            {
                drones[i].commands.push_back(toString(i)+" W 1");
                drones[i].turnFree++;
            }
        }
    }
}

int eval(int &nbOrders, vector<Order> &orders, int &nbTurns)
{
    int score = 0;
    for(int i=0;i<nbOrders;i++)
    {
        if(orders[i].turnDone >= 0)
        {
            score += int((100.0 * (nbTurns - orders[i].turnDone)) / nbTurns);
        }
    }
    return score;
}

int main(int argc, char **argv)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if(argc < 2)
    {
        cerr << "Usage: " << argv[0] << " file.in [loop]" << endl;
        return -1;
    }
    srand(time(0));
    input(rows,columns,nbDrones,nbTurns,maxLoad,nbProducts,nbWarehouses,nbOrders,weights,warehouses,orders,drones,argv[1]);
    cerr << rows << "x" << columns << " map" << endl;
    cerr << nbTurns << " ticks" << endl;
    cerr << nbDrones << " drones" << endl;
    cerr << nbProducts << " products" << endl;
    cerr << nbWarehouses << " warehouses" << endl;
    cerr << nbOrders << " orders" << endl;
    cerr << maxLoad << " max load" << endl;
    int score;
    if(argc > 2)
    {
        int best = -1;
        while(1)
        {
            compute(rows,columns,nbDrones,nbTurns,maxLoad,nbProducts,nbWarehouses,nbOrders,weights,warehouses,orders,drones);
            score = eval(nbOrders,orders,nbTurns);
            cerr << "score " << score << endl;
            if(score > best)
            {
                best = score;
                output(nbDrones,drones,score,argv[1]);
            }
            //reset
            input(rows,columns,nbDrones,nbTurns,maxLoad,nbProducts,nbWarehouses,nbOrders,weights,warehouses,orders,drones,argv[1]);
        }
    }
    else
    {
        compute(rows,columns,nbDrones,nbTurns,maxLoad,nbProducts,nbWarehouses,nbOrders,weights,warehouses,orders,drones);
        score = eval(nbOrders,orders,nbTurns);
        output(nbDrones,drones,score,argv[1]);
    }
    return 0;
}