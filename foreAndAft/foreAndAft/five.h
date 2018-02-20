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

using namespace std;

class five
{
private:
	nodeFive * five_start, *five_current, *five_succ;

public:
	int le(nodeFive *n1, nodeFive *n2);
	void getstring(string m[][sizeFive], string &s1);
	void print1puzzle(ostream &out, string m[][sizeFive]);
	void printsolution(nodeFive* n);
	void swap(string &a, string &b);
	void copy(string m[][sizeFive], string n[][sizeFive]);
	void getposition(string m[][sizeFive], string value, int &row, int &column);
	bool isSafe(int i, int j);
	int up(string m[][sizeFive], string n[][sizeFive]);
	int jumpUp(string m[][sizeFive], string n[][sizeFive]);
	int down(string m[][sizeFive], string n[][sizeFive]);
	int jumpDown(string m[][sizeFive], string n[][sizeFive]);
	int left(string m[][sizeFive], string n[][sizeFive]);
	int jumpLeft(string m[][sizeFive], string n[][sizeFive]);
	int right(string m[][sizeFive], string n[][sizeFive]);
	int jumpRight(string m[][sizeFive], string n[][sizeFive]);
	float h(string m[][sizeFive]);
	void best(string sm[][sizeFive]);
	void fiveMain();
	five();
	~five();
};

