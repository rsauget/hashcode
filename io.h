#ifndef IO_H
#define IO_H
#include <vector>
#include <string>
#include "types.h"
using namespace std;
string toString(int i);
void input(int&,int&,int&,int&,int&,int&,int&,int&,vector<int>&,vector<Warehouse>&,vector<Order>&,vector<Drone>&,string);
void output(int &,vector<Drone> &,int &,string);
#endif