//
//Fore and Aft (Homework 3)
//By Kade Walter
//CS 438
//Due Date: 2/15/2018 at 12:30 pm
//

#include "stdafx.h"
#include "heap.h"
#include "five.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <sstream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int SIZE;
string goal;
string GOAL[sizeFive][sizeFive];


struct node
{
	string m[sizeFive][sizeFive];
	float hv, gv, fv; // values of h, g, f functions
	node *parent;
	node *next;
	node(string sm[][sizeFive], node* p = 0, node* n = 0)
	{
		for (int r = 0; r < SIZE; r++)
			for (int c = 0; c < SIZE; c++)
				m[r][c] = sm[r][c];
		parent = p;
		next = n;
	}
};

class nodeheap : public heap<node *, 100000>
{
public:
	friend int le(node *n1, node *n2);  // less than or equal to
	~nodeheap()
	{
		for (int k = 0; k < heap_size; k++) delete data[k];
	}

};

int five::le(node *n1, node *n2)
{
	return ((n1->fv) > (n2->fv));
}

void five::getstring(string m[][sizeFive], string &s1)
{
	string s;
	for (int r = 0; r < SIZE; r++)
		for (int c = 0; c < SIZE; c++)
		{
			if (m[r][c] == " ")
				s += '0';
			else
				s += m[r][c];
		}
	s1 = s;
}

void five::print1puzzle(ostream &out, string m[][sizeFive])
{
	out << setiosflags(ios::fixed | ios::showpoint)
		<< setprecision(2);

	for (int r = 0; r < SIZE; r++)
	{
		for (int c = 0; c < SIZE; c++)
			out << m[r][c];
		out << endl;
	}
}

void five::printsolution(node* n)
{


	string sizeString = to_string(SIZE);
	ofstream file(sizeString + "BEST.out");

	while (n->parent)
	{

		n->parent->next = n;
		n = n->parent;
	}

	int count = -1;
	while (n)
	{
		count++;
		print1puzzle(file, n->m);
		file << "State " << count << endl << endl;

		n = n->next;
	}
	file << "Solution has " << count << " steps.\n\n";
	cout << "Puzzle solved in " << count << " steps.\n\n";
}

void five::swap(string &a, string &b)
{
	string tmp = a;
	a = b;
	b = tmp;
}

void five::copy(string m[][sizeFive], string n[][sizeFive])
{
	for (int r = 0; r < SIZE; r++)
		for (int c = 0; c < SIZE; c++)
			n[r][c] = m[r][c];
}

void five::getposition(string m[][sizeFive], string value, int &row, int &column)
{
	for (int r = 0; r < SIZE; r++)
		for (int c = 0; c < SIZE; c++)
		{
			if (m[r][c] == value)
			{
				row = r; column = c;
			}
		}
}

bool five::isSafe(int i, int j)
{
	int halfSize = (SIZE - 1) / 2;
	if (i >= 0 && i < SIZE && j >= 0 && j < SIZE)
	{
		if (GOAL[i][j] == "#")
			return false;
		return true;
	}
	else
		return false;
}

int five::up(string m[][sizeFive], string n[][sizeFive])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(r0 - 1, c0))
	{
		swap(n[r0][c0], n[r0 - 1][c0]);
		return 1;
	}
	else
		return 0;
}

int five::jumpUp(string m[][sizeFive], string n[][sizeFive])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(r0 - 2, c0))
	{
		swap(n[r0][c0], n[r0 - 2][c0]);
		return 1;
	}
	else
		return 0;
}

int five::down(string m[][sizeFive], string n[][sizeFive])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(r0 + 1, c0))
	{
		swap(n[r0][c0], n[r0 + 1][c0]);
		return 1;
	}
	else
		return 0;
}

int five::jumpDown(string m[][sizeFive], string n[][sizeFive])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(r0 + 2, c0))
	{
		swap(n[r0][c0], n[r0 + 2][c0]);
		return 1;
	}
	else
		return 0;
}

int five::left(string m[][sizeFive], string n[][sizeFive])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(r0, c0 - 1))
	{
		swap(n[r0][c0], n[r0][c0 - 1]);
		return 1;
	}
	else
		return 0;
}

int five::jumpLeft(string m[][sizeFive], string n[][sizeFive])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(r0, c0 - 2))
	{
		swap(n[r0][c0], n[r0][c0 - 2]);
		return 1;
	}
	else
		return 0;
}

int five::right(string m[][sizeFive], string n[][sizeFive])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(r0, c0 + 1))
	{
		swap(n[r0][c0], n[r0][c0 + 1]);
		return 1;
	}
	else
		return 0;
}

int five::jumpRight(string m[][sizeFive], string n[][sizeFive])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(r0, c0 + 2))
	{
		swap(n[r0][c0], n[r0][c0 + 2]);
		return 1;
	}
	else
		return 0;
}

// f(n) = g(n) + C*H2(n)

float C = 5.0;

float five::h(string m[][sizeFive])
{
	int halfSize = (SIZE - 1) / 2;
	int redTotal = 0, blueTotal = 0, topLeftGoal = 108, botRightGoal = 36;
	int r, c, dr, dc, l = 0, cur = 1, total_distance = 0,
		ok = 1;
	/*for (cur = 1; cur <= 15; cur++)
	{
	getposition(m, cur, r, c);
	dr = (cur - 1) / SIZE;
	dc = (cur - 1) % SIZE;
	total_distance += td(r, c, dr, dc);
	}*/
	for (int i = 0; i <= halfSize; i++)
	{
		for (int j = 0; j <= halfSize; j++)
		{
			if (m[i][j] != "B")
			{
				total_distance += 1;
			}
		}
	}
	for (int i = halfSize; i < SIZE; i++)
	{
		for (int j = halfSize; j <= SIZE; j++)
		{
			if (m[i][j] == "B")
			{
				total_distance += 1;
			}
		}
	}
	return C * total_distance;

}


void five::best(string sm[][sizeFive])
{

	node *start, *current, *succ;
	nodeheap open;
	set<string> close;
	string s;

	start = new node(sm);
	start->gv = 0; // cost so far is 0
	open.push_heap(start);

	getstring(sm, s);
	close.insert(s);

	string temp[sizeFive][sizeFive];
	int success = 0;

	long gencount = 1;

	while (!open.heap_empty() && !success)
	{
		open.pop_heap(current);
		getstring(current->m, s);
		if (s == goal)
		{
			printsolution(current);
			success = 1;
		}
		else // s is not goal
		{
			if (current->parent != NULL)
				getstring(current->parent->m, s);
			else
				s = "";
			float fv, gv, hv;
			if (up(current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					succ = new node(temp, current);
					succ->hv = h(temp);
					succ->gv = (current->gv) + 1;
					succ->fv = succ->hv + succ->gv;
					open.push_heap(succ);
					gencount++;
				}
			}
			if (right(current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					succ = new node(temp, current);
					succ->hv = hv = h(temp);
					succ->gv = gv = (current->gv) + 1;
					succ->fv = hv + gv;
					open.push_heap(succ);
					gencount++;
				}
			}
			if (left(current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					succ = new node(temp, current);
					succ->hv = hv = h(temp);
					succ->gv = gv = (current->gv) + 1;
					succ->fv = hv + gv;
					open.push_heap(succ);
					gencount++;
				}
			}
			if (down(current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					succ = new node(temp, current);
					succ->hv = hv = h(temp);
					succ->gv = gv = (current->gv) + 1;
					succ->fv = hv + gv;
					open.push_heap(succ);
					gencount++;
				}
			}
			if (jumpUp(current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					succ = new node(temp, current);
					succ->hv = h(temp);
					succ->gv = (current->gv) + 1;
					succ->fv = succ->hv + succ->gv;
					open.push_heap(succ);
					gencount++;
				}
			}
			if (jumpRight(current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					succ = new node(temp, current);
					succ->hv = hv = h(temp);
					succ->gv = gv = (current->gv) + 1;
					succ->fv = hv + gv;
					open.push_heap(succ);
					gencount++;
				}
			}
			if (jumpLeft(current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					succ = new node(temp, current);
					succ->hv = hv = h(temp);
					succ->gv = gv = (current->gv) + 1;
					succ->fv = hv + gv;
					open.push_heap(succ);
					gencount++;
				}
			}
			if (jumpDown(current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					succ = new node(temp, current);
					succ->hv = hv = h(temp);
					succ->gv = gv = (current->gv) + 1;
					succ->fv = hv + gv;
					open.push_heap(succ);
					gencount++;
				}
			}
		}
	}
	cout << gencount << " nodes visted.\n";
}

void five::fiveMain()
{
	int size = 5;
	string GAME_BOARD[sizeFive][sizeFive];
	SIZE = size;
	int halfSize = (SIZE - 1) / 2;
	//creating the gameboard
	for (int i = 0; i < size; i++)
	{
		if (i < halfSize)
		{
			int j = 0;
			for (j; j <= halfSize; j++)
			{
				GAME_BOARD[i][j] = "R";
			}
			for (j; j < size; j++)
			{
				GAME_BOARD[i][j] = "#";
			}
		}
		else if (i == halfSize)
		{
			int j = 0;
			for (j; j < halfSize; j++)
			{
				GAME_BOARD[i][j] = "R";
			}
			GAME_BOARD[i][j] = " ";
			j++;
			for (j; j < size; j++)
			{
				GAME_BOARD[i][j] = "B";
			}
		}
		else if (i > halfSize)
		{
			int j = 0;
			for (j; j < halfSize; j++)
			{
				GAME_BOARD[i][j] = "#";
			}
			for (j; j < size; j++)
			{
				GAME_BOARD[i][j] = "B";
			}
		}
	}
	//creating the goal matrix
	for (int i = 0; i < size; i++)
	{
		if (i < halfSize)
		{
			int j = 0;
			for (j; j <= halfSize; j++)
			{
				GOAL[i][j] = "B";
			}
			for (j; j < size; j++)
			{
				GOAL[i][j] = "#";
			}
		}
		else if (i == halfSize)
		{
			int j = 0;
			for (j; j < halfSize; j++)
			{
				GOAL[i][j] = "B";
			}
			GOAL[i][j] = " ";
			j++;
			for (j; j < size; j++)
			{
				GOAL[i][j] = "R";
			}
		}
		else if (i > halfSize)
		{
			int j = 0;
			for (j; j < halfSize; j++)
			{
				GOAL[i][j] = "#";
			}
			for (j; j < size; j++)
			{
				GOAL[i][j] = "R";
			}
		}
	}
	best(GAME_BOARD);
}

five::five()
{
}


five::~five()
{
}
