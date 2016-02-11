#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "io.h"

using namespace std;

void input(int &t, int &n, int &m)
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

void output(int &t, int &n, int &m, int &s)
{
	ofstream out("out");
	out << "hello" << endl;
	system(("cp out out." + to_string(time(0)) + to_string(s)).c_str());
}