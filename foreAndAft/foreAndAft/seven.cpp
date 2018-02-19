#include "stdafx.h"
#include "structs.h"
#include "sevenHeap.h"
#include "seven.h"

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

using namespace std;

//possible goalFive solutions
const string GOAL_SEVEN = "BBBB###BBBB###BBBB###BBB0RRR###RRRR###RRRR###RRRR";

int SEVEN_SIZE;
string goalSeven;
string GOAL_SEVEN_MATRIX[sizeSeven][sizeSeven];


class nodeheap : public heap<nodeSeven *, 100000>
{
public:
	friend int seven::le(nodeSeven *n1, nodeSeven *n2);  // less than or equal to
	~nodeheap()
	{
		for (int k = 0; k < heap_size; k++) delete data[k];
	}

};

int seven::le(nodeSeven *n1, nodeSeven *n2)
{
	return ((n1->fv) >(n2->fv));
}

void seven::getstring(string m[][sizeSeven], string &s1)
{
	string s;
	for (int r = 0; r < SEVEN_SIZE; r++)
		for (int c = 0; c < SEVEN_SIZE; c++)
		{
			if (m[r][c] == " ")
				s += '0';
			else
				s += m[r][c];
		}
	s1 = s;
}

void seven::print1puzzle(ostream &out, string m[][sizeSeven])
{
	out << setiosflags(ios::fixed | ios::showpoint)
		<< setprecision(2);

	for (int r = 0; r < SEVEN_SIZE; r++)
	{
		for (int c = 0; c < SEVEN_SIZE; c++)
			out << m[r][c];
		out << endl;
	}
}

void seven::printsolution(nodeSeven* n)
{


	string sizeString = to_string(SEVEN_SIZE);
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

void seven::swap(string &a, string &b)
{
	string tmp = a;
	a = b;
	b = tmp;
}

void seven::copy(string m[][sizeSeven], string n[][sizeSeven])
{
	for (int r = 0; r < SEVEN_SIZE; r++)
		for (int c = 0; c < SEVEN_SIZE; c++)
			n[r][c] = m[r][c];
}

void seven::getposition(string m[][sizeSeven], string value, int &row, int &column)
{
	for (int r = 0; r < SEVEN_SIZE; r++)
		for (int c = 0; c < SEVEN_SIZE; c++)
		{
			if (m[r][c] == value)
			{
				row = r; column = c;
			}
		}
}

bool seven::isSafe(int i, int j)
{
	int halfSize = (SEVEN_SIZE - 1) / 2;
	if (i >= 0 && i < SEVEN_SIZE && j >= 0 && j < SEVEN_SIZE)
	{
		if (GOAL_SEVEN_MATRIX[i][j] == "#")
			return false;
		return true;
	}
	else
		return false;
}

int seven::up(string m[][sizeSeven], string n[][sizeSeven])
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

int seven::jumpUp(string m[][sizeSeven], string n[][sizeSeven])
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

int seven::down(string m[][sizeSeven], string n[][sizeSeven])
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

int seven::jumpDown(string m[][sizeSeven], string n[][sizeSeven])
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

int seven::left(string m[][sizeSeven], string n[][sizeSeven])
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

int seven::jumpLeft(string m[][sizeSeven], string n[][sizeSeven])
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

int seven::right(string m[][sizeSeven], string n[][sizeSeven])
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

int seven::jumpRight(string m[][sizeSeven], string n[][sizeSeven])
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

float SEVEN_C = 5.0;

float seven::h(string m[][sizeSeven])
{
	int halfSize = (SEVEN_SIZE - 1) / 2;
	int goalBlueTotal = 183;
	int currBlueTotal = 0;
	int total_distance = 0;

	for (int i = 0; i < SEVEN_SIZE; i++)
	{
		for (int j = 0; j < SEVEN_SIZE; j++)
		{
			if (m[i][j] == "B")
			{
				int temp = (SEVEN_SIZE * i) + (j + 1);
				currBlueTotal += temp;
			}
		}
	}

	total_distance = currBlueTotal - goalBlueTotal;
	return SEVEN_C * total_distance;

}


void seven::best(string sm[][sizeSeven])
{

	nodeSeven *start, *current, *succ;
	nodeheap open;
	set<string> close;
	string s;

	start = new nodeSeven(sm);
	start->gv = 0; // cost so far is 0
	open.push_heap(start);

	getstring(sm, s);
	close.insert(s);

	string temp[sizeSeven][sizeSeven];
	int success = 0;

	long gencount = 1;

	while (!open.heap_empty() && !success)
	{
		open.pop_heap(current);
		getstring(current->m, s);
		if (s == GOAL_SEVEN)
		{
			printsolution(current);
			success = 1;
		}
		else // s is not goalFive
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
					succ = new nodeSeven(temp, current);
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
					succ = new nodeSeven(temp, current);
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
					succ = new nodeSeven(temp, current);
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
					succ = new nodeSeven(temp, current);
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
					succ = new nodeSeven(temp, current);
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
					succ = new nodeSeven(temp, current);
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
					succ = new nodeSeven(temp, current);
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
					succ = new nodeSeven(temp, current);
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

void seven::sevenMain()
{
	int size = sizeSeven;
	string GAME_BOARD[sizeSeven][sizeSeven];
	SEVEN_SIZE = size;
	goalSeven = GOAL_SEVEN;
	int halfSize = (SEVEN_SIZE - 1) / 2;
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
	//creating the goalFive matrix
	for (int i = 0; i < size; i++)
	{
		if (i < halfSize)
		{
			int j = 0;
			for (j; j <= halfSize; j++)
			{
				GOAL_SEVEN_MATRIX[i][j] = "B";
			}
			for (j; j < size; j++)
			{
				GOAL_SEVEN_MATRIX[i][j] = "#";
			}
		}
		else if (i == halfSize)
		{
			int j = 0;
			for (j; j < halfSize; j++)
			{
				GOAL_SEVEN_MATRIX[i][j] = "B";
			}
			GOAL_SEVEN_MATRIX[i][j] = " ";
			j++;
			for (j; j < size; j++)
			{
				GOAL_SEVEN_MATRIX[i][j] = "R";
			}
		}
		else if (i > halfSize)
		{
			int j = 0;
			for (j; j < halfSize; j++)
			{
				GOAL_SEVEN_MATRIX[i][j] = "#";
			}
			for (j; j < size; j++)
			{
				GOAL_SEVEN_MATRIX[i][j] = "R";
			}
		}
	}
	best(GAME_BOARD);
}

seven::seven()
{
}


seven::~seven()
{
}
