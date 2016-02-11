#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include "io.h"

using namespace std;

string toString(int i)
{
	ostringstream oss;
	oss<<i;
	return oss.str();
}

void input(vector<vector<int> > &t, int &n, int &m, int &v)
{
	string s;
	cin >> v;
	cin.ignore(1, ',');
	cin >> v;
	cin.ignore(1, ',');
	cin >> v;
	cin.ignore(1, ',');
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin >> t[i][j];
			cin.ignore(1,',');
		}
	}
}

void output(vector<vector<int> > &t, int &n, int &m, int &s)
{
	ofstream out("out/" + toString(s) + "-" + toString(time(0)));
	out << "hello" << endl;
	out.close();
}
