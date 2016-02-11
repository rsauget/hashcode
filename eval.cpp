#include <vector>
#include <ctgmath>
#include "eval.h"
using namespace std;
int eval(int &nbOrders, vector<Order> &orders, int &nbTicks)
{
	int score = 0;
	for(int i=0;i<nbOrders;i++)
	{
		if(orders[i].turnDone >= 0)
		{
			score += ceil(100 * (nbTicks - orders[i].turnDone) / nbTicks);
		}
	}
	return score;
}