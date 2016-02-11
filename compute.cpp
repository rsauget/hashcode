#include <vector>
#include "compute.h"
using namespace std;

double distance(int r1, int c1, int r2, int c2) {
    double distance = sqrt((r1-r2)*(r1-r2) + (c1-c2)*(c1-c2));
}

void compute(vector<vector<int> > &t, int &n, int &m)
{
    while(true) {
        for(int turn = 0; turn < nbTicks; turn++) {
            //find an objective for all free drones
            for(auto d : drones) {
                if(drone.turnFree < turn)
                    continue;

                for(auto o : orders) {
                    double droneToOrder = distance(drone.row, drone.column, o.row, o.column);
                    if(droneToOrder > TODO)
                        continue;
                    for(auto p : o.products) {
                        int productDistance = 
                        for(auto w : warehouses) {
                            if(w.items[p] == 0)
                                continue;
                            productDistance = distance(drone.row, drone.column, o.row, o.column);
                        }
                    } 
                }

            }
        }
    }
}