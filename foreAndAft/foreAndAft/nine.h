#pragma once
#include "stdafx.h"
#include "structs.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <set>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

class nine
{
private:
	nodeNine * nine_start, *nine_current, *nine_succ;

public:
	int le(nodeNine *n1, nodeNine *n2);
	void getstring(string m[][sizeNine], string &s1);
	void print1puzzle(ostream &out, string m[][sizeNine]);
	void printsolution(nodeNine* n);
	void swap(string &a, string &b);
	void copy(string m[][sizeNine], string n[][sizeNine]);
	void getposition(string m[][sizeNine], string value, int &row, int &column);
	bool isSafe(int i, int j);
	int up(string m[][sizeNine], string n[][sizeNine]);
	int jumpUp(string m[][sizeNine], string n[][sizeNine]);
	int down(string m[][sizeNine], string n[][sizeNine]);
	int jumpDown(string m[][sizeNine], string n[][sizeNine]);
	int left(string m[][sizeNine], string n[][sizeNine]);
	int jumpLeft(string m[][sizeNine], string n[][sizeNine]);
	int right(string m[][sizeNine], string n[][sizeNine]);
	int jumpRight(string m[][sizeNine], string n[][sizeNine]);
	float h(string m[][sizeNine]);
	void best(string sm[][sizeNine]);
	void nineMain();
	nine();
	~nine();
};

