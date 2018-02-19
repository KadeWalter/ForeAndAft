#pragma once
#include <string>

using namespace std;

const int sizeFive = 5;
const int sizeSeven = 7;
const int sizeNine = 9;
const int SizeEle = 11;

struct nodeFive
{
	string m[5][5];
	float hv, gv, fv; // values of h, g, f functions
	nodeFive *parent;
	nodeFive *next;
	nodeFive(string sm[][5], nodeFive* p = 0, nodeFive* n = 0)
	{
		for (int r = 0; r<5; r++)
			for (int c = 0; c<5; c++)
				m[r][c] = sm[r][c];
		parent = p;
		next = n;
	}
};

struct nodeSeven
{
	string m[7][7];
	float hv, gv, fv; // values of h, g, f functions
	nodeSeven *parent;
	nodeSeven *next;
	nodeSeven(string sm[][7], nodeSeven* p = 0, nodeSeven* n = 0)
	{
		for (int r = 0; r<7; r++)
			for (int c = 0; c<7; c++)
				m[r][c] = sm[r][c];
		parent = p;
		next = n;
	}
};

struct nodeNine
{
	string m[9][9];
	float hv, gv, fv; // values of h, g, f functions
	nodeNine *parent;
	nodeNine *next;
	nodeNine(string sm[][9], nodeNine* p = 0, nodeNine* n = 0)
	{
		for (int r = 0; r<9; r++)
			for (int c = 0; c<9; c++)
				m[r][c] = sm[r][c];
		parent = p;
		next = n;
	}
};

struct nodeEle
{
	string m[11][11];
	float hv, gv, fv; // values of h, g, f functions
	nodeEle *parent;
	nodeEle *next;
	nodeEle(string sm[][11], nodeEle* p = 0, nodeEle* n = 0)
	{
		for (int r = 0; r<11; r++)
			for (int c = 0; c<11; c++)
				m[r][c] = sm[r][c];
		parent = p;
		next = n;
	}
};