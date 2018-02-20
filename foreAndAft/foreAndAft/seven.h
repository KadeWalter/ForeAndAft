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

class seven
{
private:
	nodeSeven * seven_start, *seven_current, *seven_succ;
public:

	int le(nodeSeven *n1, nodeSeven *n2);
	void getstring(string m[][sizeSeven], string &s1);
	void print1puzzle(ostream &out, string m[][sizeSeven]);
	void printsolution(nodeSeven* n);
	void swap(string &a, string &b);
	void copy(string m[][sizeSeven], string n[][sizeSeven]);
	void getposition(string m[][sizeSeven], string value, int &row, int &column);
	bool isSafe(int i, int j);
	int up(string m[][sizeSeven], string n[][sizeSeven]);
	int jumpUp(string m[][sizeSeven], string n[][sizeSeven]);
	int down(string m[][sizeSeven], string n[][sizeSeven]);
	int jumpDown(string m[][sizeSeven], string n[][sizeSeven]);
	int left(string m[][sizeSeven], string n[][sizeSeven]);
	int jumpLeft(string m[][sizeSeven], string n[][sizeSeven]);
	int right(string m[][sizeSeven], string n[][sizeSeven]);
	int jumpRight(string m[][sizeSeven], string n[][sizeSeven]);
	float h(string m[][sizeSeven]);
	void best(string sm[][sizeSeven]);
	void sevenMain();
	seven();
	~seven();
};

