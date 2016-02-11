#include <iostream>
#include <string>
#include "io.h"

using namespace std;

extern int **t;
extern int M;
extern int N;

void read()
{
	string s;
	cin >> s;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			cin >> t[i][j];
			cin.ignore(1,',');
		}
	}
}

void write()
{
	system("cp out out." + time(0));
}