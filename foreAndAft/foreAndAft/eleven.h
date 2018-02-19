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

class eleven
{
public:

	int le(nodeEle *n1, nodeEle *n2);
	void getstring(string m[][SizeEle], string &s1);
	void print1puzzle(ostream &out, string m[][SizeEle]);
	void printsolution(nodeEle* n);
	void swap(string &a, string &b);
	void copy(string m[][SizeEle], string n[][SizeEle]);
	void getposition(string m[][SizeEle], string value, int &row, int &column);
	bool isSafe(int i, int j);
	int up(string m[][SizeEle], string n[][SizeEle]);
	int jumpUp(string m[][SizeEle], string n[][SizeEle]);
	int down(string m[][SizeEle], string n[][SizeEle]);
	int jumpDown(string m[][SizeEle], string n[][SizeEle]);
	int left(string m[][SizeEle], string n[][SizeEle]);
	int jumpLeft(string m[][SizeEle], string n[][SizeEle]);
	int right(string m[][SizeEle], string n[][SizeEle]);
	int jumpRight(string m[][SizeEle], string n[][SizeEle]);
	float h(string m[][SizeEle]);
	void best(string sm[][SizeEle]);
	void eleMain();
	eleven();
	~eleven();
};

