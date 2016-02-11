#include <iostream>
#include <string>
#include <vector>
#include "io.h"
#include "draw.h"
#include "compute.h"
#include "eval.h"

using namespace std;

int n=300;
int m=300;
int zoom=2;

int v;
vector<vector<int> > t;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	t = vector<vector<int> >(n, vector<int>(m,0));
	input(t,n,m,v);
	//draw(t,n,m,zoom);
	int best = -1;
	int score;
	while(1)
	{
		compute(t,n,m);
		score = eval(t,n,m);
		if(score > best)
		{
			best = score;
			output(t,n,m,score);
		}
	}
	return 0;
}