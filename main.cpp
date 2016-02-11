#include <iostream>
#include <string>
#include "io.h"
#include "draw.h"
#include "compute.h"
#include "eval.h"

using namespace std;

const int n=300;
const int m=300;
const int zoom=2;

int v;
int t[n][m];

int eval(int &t, int &n, int &m)
{
	return -1;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	input(t,n,m);
	draw(t,n,m);
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