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

class el
{
public:

	int le(nodeEleven *n1, nodeEleven *n2);
	void getstring(string m[][sizeEle], string &s1);
	void print1puzzle(ostream &out, string m[][sizeEle]);
	void printsolution(nodeEleven* n);
	void swap(string &a, string &b);
	void copy(string m[][sizeEle], string n[][sizeEle]);
	void getposition(string m[][sizeEle], string value, int &row, int &column);
	bool isSafe(int i, int j);
	int up(string m[][sizeEle], string n[][sizeEle]);
	int jumpUp(string m[][sizeEle], string n[][sizeEle]);
	int down(string m[][sizeEle], string n[][sizeEle]);
	int jumpDown(string m[][sizeEle], string n[][sizeEle]);
	int left(string m[][sizeEle], string n[][sizeEle]);
	int jumpLeft(string m[][sizeEle], string n[][sizeEle]);
	int right(string m[][sizeEle], string n[][sizeEle]);
	int jumpRight(string m[][sizeEle], string n[][sizeEle]);
	float h(string m[][sizeEle]);
	void best(string sm[][sizeEle]);
	void elMain();
};

