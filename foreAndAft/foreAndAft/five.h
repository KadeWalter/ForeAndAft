#pragma once
#include "stdafx.h"
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

class five
{
public:
	//possible goal solutions
	const string goalFive = "BBB##BBB##BB0RR##RRR##RRR";
	const string goalSeven = "BBBB###BBBB###BBBB###BBB0RRR###RRRR###RRRR###RRRR";
	const string goalNine = "BBBBB####BBBBB####BBBBB####BBBBB####BBBB0RRRR####RRRRR####RRRRR####RRRRR####RRRRR";
	const string goalEleven = "BBBBBB#####BBBBBB#####BBBBBB#####BBBBBB#####BBBBBB#####BBBBB0RRRRR#####RRRRRR#####RRRRRR#####RRRRRR#####RRRRRR#####RRRRRR";
	//possible game sizes
	const int sizeFive = 5;
	const int sizeSeven = 7;
	const int sizeNine = 9;
	const int sizeEleven = 11;
	
	int le(node *n1, node *n2);
	void getstring(string m[][sizeFive], string &s1);
	void print1puzzle(ostream &out, string m[][sizeFive]);
	void printsolution(node* n);
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

