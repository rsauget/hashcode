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
typedef pair<ii,ii> pii;

double compute_distance(int r1, int c1, int r2, int c2) {
   	return sqrt((r1-r2)*(r1-r2) + (c1-c2)*(c1-c2));
}

vector<ii> chose_objects(vector<ii> &products,Warehouse &w,vector<int> &weights,int maxLoad)
{
	int weightTaken = 0;
	      
	vector<pair<int,int> > objectTaken;
	for(int p=0;p<products.size();++p)
	{
		int type = products[p].first;
		int cap =  products[p].second;
		if(cap==0)
			continue;
		int mincap = min(cap,w.products[type]);
		int weight = weights[type];
		if(mincap*weight+weightTaken<=maxLoad && mincap>0)
		{
			weightTaken+=mincap*weight;
			objectTaken.push_back(make_pair(type,mincap));
		}
		else if(mincap>0)
		{
			int k = (maxLoad - weightTaken)/weight;
			mincap = min(mincap,k);
			if(mincap>0)
			{
				objectTaken.push_back(make_pair(type,mincap));
				weightTaken+= mincap*weight;
			}
		}
	}
    return objectTaken;
}

vector<ii> knapsack(vector<ii> &products,Warehouse &w,vector<int> &weights,int maxLoad)
{
	int weightTaken = 0;
	vector<ii> load[maxLoad+1];
	bool okay = false;
	map<int,vector<ii> >::reverse_iterator it;
	for(int p=0;p<products.size();++p)
	{
		int type = products[p].first;
		int cap = products[p].second;
		if(cap==0)
			continue;
		int mincap = min(cap,w.products[type]);

		int weight = weights[type];
		int k = maxLoad/weight;
		mincap = min(mincap,k);
		if(mincap>0)
		{
			for(int j = maxLoad;j>=0;--j)
			{
				if(load[j].size()==0 && j!=0)
					continue;
				int l = (maxLoad-j)/weight;
				int aux=min(mincap,l);
				int k = j+aux*weight;
				if(aux>0 && k<=maxLoad)
				{			
					if(load[k].size()>0)
					{
						load[k]=load[j];
						load[k].push_back(make_pair(type,aux));
					}
					else if(load[k].size()<=load[j].size())
					{
						load[k]=load[j];
						load[k].push_back(make_pair(type,aux));
					}
					okay=true;
				}
			}
		}
	}
	int maximum=0;
	int pos;
	for(int i=0;i<=maxLoad;++i)
	{
		if(load[i].size()>=maximum)
		{
			maximum=load[i].size();
			pos=i;
		}
	}
	if(maximum==0)
		return chose_objects(products,w,weights,maxLoad);
    return load[pos];
}



void compute(int &rows,int &columns,int &nbDrones,int &nbTicks,int &maxLoad,int &nbProducts,int &nbWarehouses,int &nbOrders,vector<int> &weights,vector<Warehouse> &warehouses,vector<Order> &orders, vector<Drone> &drones)
{

	for(int i=0;i<drones.size();++i)
		drones[i].turnFree=0;

    for(int turn = 0; turn < nbTicks; turn++) 
    {
        //cout << turn << endl;
        int completed=0;
        for(int i=0;i<orders.size();++i)
        	if(orders[i].nbProducts==0 && orders[i].turnDone<=turn)
        		completed++;
        int cntNbProdToDel = 0;
        for(int i=0;i<orders.size();++i)
       		for(int j=0;j<orders[i].products.size();++j)
       			cntNbProdToDel += orders[i].products[j].second;
       	if(cntNbProdToDel==0)
       		continue;
        cerr<<turn<<" "<<cntNbProdToDel<<"    "<<completed<<endl;
        //find an objective for all free drones
	    int vis[nbDrones];
	    for(int i=0;i<nbDrones;++i)
	    {
	    	if(drones[i].turnFree==turn)
	    		vis[i]=0;
	    	else vis[i]=1;
	    }
	    int beta=0;
	    while(beta<nbDrones*2)
	    {
	    	double bestOrderScore = nbTicks;
	    	int chosenOrder = -1;
	    	vector<pair<int,int> > bestProducts;
	    	int chosenWarehouse = -1;
	    	int bestDrone=-1;
	        for(int d=0; d<drones.size(); ++d)
	        {
	            
	            int alpha = drones[d].turnFree - turn;
	            if(alpha <0)
	            	cerr<<"problem "<<alpha<<endl;
	            pii minMove;
	            bool completeGlobal=false;

	            //TODO : take multiples products

	            for(int o=0;o<orders.size();++o) {
	                if(orders[o].nbProducts==0)
	                    continue;
	                vector<pair<int,int> > bestObjectsTaken;
	          		double bestWareScore= nbTicks;
	          		int localWarehouse =-1;
	          		bool completeLocal = false;

	                for(int w = 0; w<warehouses.size();++w)
	               	{
	                	vector<pair<int,int> > objectTaken = knapsack(orders[o].products,warehouses[w],weights,maxLoad);
	              

	                	double productDistance = compute_distance(orders[o].row, orders[o].column, warehouses[w].row, warehouses[w].column);
	                    double droneToWare = compute_distance(drones[d].row, drones[d].column, warehouses[w].row, warehouses[w].column);
	                    double dist = productDistance + droneToWare;
	                    
	                    double x = objectTaken.size();
	                	int score = ceil(dist)+alpha+2*x+turn;
	                	int aux=0;
	                	for(int i=0;i<objectTaken.size();++i)
	                		aux+=objectTaken[i].second;
	                	if(aux!=orders[o].nbProducts)
	                		score+=20;
	                	if(score<bestWareScore && x>0)
	                	{
	                		bestWareScore = score;
	                		bestObjectsTaken = objectTaken;
	                		localWarehouse = w;
	                	}
	                }
	                if(bestOrderScore>bestWareScore)
	                {
	                	bestOrderScore = bestWareScore;
	                	bestProducts = bestObjectsTaken;
	                	chosenWarehouse = localWarehouse;
	                	chosenOrder = o;
	                	bestDrone = d;
	                }
	            }    
		    }
		    beta++;
		    if(chosenOrder==-1)
		        continue;
		            
            int o = chosenOrder;
            int w = chosenWarehouse;
            int d = bestDrone;

            double productDistance = compute_distance(orders[o].row, orders[o].column, warehouses[w].row, warehouses[w].column);
            double droneToWare = compute_distance(drones[d].row, drones[d].column, warehouses[w].row, warehouses[w].column);
            double dist = productDistance + droneToWare;

            drones[d].turnFree += ceil(dist) + 2*bestProducts.size();
            drones[d].row = orders[o].row;
            drones[d].column = orders[o].column;

            int cntNbProducts=0;
            for(int i=0;i<bestProducts.size();++i)
            {
            	int type = bestProducts[i].first;
            	int cap = bestProducts[i].second;
            	cntNbProducts+=cap;
            	warehouses[w].products[type]-=cap;
           		for(int j=0;j<orders[o].products.size();++j)
           		{
           			int localType = orders[o].products[j].first;
           			if(localType==type)
           			{
           				orders[o].products[j].second-=cap;
           				break;
           			}
           		}
            }
            orders[o].nbProducts-=cntNbProducts;
            if(orders[o].nbProducts==0)
            	orders[o].turnDone = drones[d].turnFree;
            vis[d]=1;
            for(int i=0;i<bestProducts.size();++i)
            {
            	int type = bestProducts[i].first;
            	int cap = bestProducts[i].second;
            	drones[d].commands.push_back(toString(d) + " L " + toString(w)  + " " + toString(type) + " "+ toString(cap));
            }
            for(int i=0;i<bestProducts.size();++i)
            {
            	int type = bestProducts[i].first;
            	int cap = bestProducts[i].second;
            	drones[d].commands.push_back(toString(d) + " D " + toString(o) + " " + toString(type) + " "+ toString(cap));
            }
	    }
	    for(int i=0;i<nbDrones;++i)
	    {
	    	if(!vis[i])
	    	{
	    		drones[i].commands.push_back(toString(i)+" W 1");
	    		drones[i].turnFree++;
	    	}
	    }
    }
}