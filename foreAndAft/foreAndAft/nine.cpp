#include "stdafx.h"
#include "structs.h"
#include "nineHeap.h"
#include "nine.h"

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

//possible goalNine solutions
const string GOAL_NINE = "BBBBB####BBBBB####BBBBB####BBBBB####BBBB0RRRR####RRRRR####RRRRR####RRRRR####RRRRR";

int NINE_SIZE;
string goalNine;
string GOAL_NINE_MATRIX[sizeNine][sizeNine];


class nodeheap : public heap<nodeNine *, 100000>
{
public:
	friend int nine::le(nodeNine *n1, nodeNine *n2);  // less than or equal to
	~nodeheap()
	{
		for (int k = 0; k < heap_size; k++) delete data[k];
	}

};

int nine::le(nodeNine *n1, nodeNine *n2)
{
	return ((n1->fv) >(n2->fv));
}

void nine::getstring(string m[][sizeNine], string &s1)
{
	string s;
	for (int r = 0; r < NINE_SIZE; r++)
		for (int c = 0; c < NINE_SIZE; c++)
		{
			if (m[r][c] == " ")
				s += '0';
			else
				s += m[r][c];
		}
	s1 = s;
}

void nine::print1puzzle(ostream &out, string m[][sizeNine])
{
	out << setiosflags(ios::fixed | ios::showpoint)
		<< setprecision(2);

	for (int r = 0; r < NINE_SIZE; r++)
	{
		for (int c = 0; c < NINE_SIZE; c++)
			out << m[r][c];
		out << endl;
	}
}

void nine::printsolution(nodeNine* n)
{


	string sizeString = to_string(NINE_SIZE);
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

void nine::swap(string &a, string &b)
{
	string tmp = a;
	a = b;
	b = tmp;
}

void nine::copy(string m[][sizeNine], string n[][sizeNine])
{
	for (int r = 0; r < NINE_SIZE; r++)
		for (int c = 0; c < NINE_SIZE; c++)
			n[r][c] = m[r][c];
}

void nine::getposition(string m[][sizeNine], string value, int &row, int &column)
{
	for (int r = 0; r < NINE_SIZE; r++)
		for (int c = 0; c < NINE_SIZE; c++)
		{
			if (m[r][c] == value)
			{
				row = r; column = c;
			}
		}
}

bool nine::isSafe(int i, int j)
{
	int halfSize = (NINE_SIZE - 1) / 2;
	if (i >= 0 && i < NINE_SIZE && j >= 0 && j < NINE_SIZE)
	{
		if (GOAL_NINE_MATRIX[i][j] == "#")
			return false;
		return true;
	}
	else
		return false;
}

int nine::up(string m[][sizeNine], string n[][sizeNine])
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

int nine::jumpUp(string m[][sizeNine], string n[][sizeNine])
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

int nine::down(string m[][sizeNine], string n[][sizeNine])
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

int nine::jumpDown(string m[][sizeNine], string n[][sizeNine])
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

int nine::left(string m[][sizeNine], string n[][sizeNine])
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

int nine::jumpLeft(string m[][sizeNine], string n[][sizeNine])
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

int nine::right(string m[][sizeNine], string n[][sizeNine])
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

int nine::jumpRight(string m[][sizeNine], string n[][sizeNine])
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

float NINE_C = 10.0;

float nine::h(string m[][sizeNine])
{
	int halfSize = (NINE_SIZE - 1) / 2;
	int goalBlueTotal = 484;
	int currBlueTotal = 0;
	int total_distance = 0;

	for (int i = 0; i < NINE_SIZE; i++)
	{
		for (int j = 0; j < NINE_SIZE; j++)
		{
			if (m[i][j] == "B")
			{
				int temp = (NINE_SIZE * i) + (j + 1);
				currBlueTotal += temp;
			}
		}
	}

	total_distance = currBlueTotal - goalBlueTotal;
	return NINE_C * total_distance;

}


void nine::best(string sm[][sizeNine])
{

	nodeNine *start, *current, *succ;
	nodeheap open;
	set<string> close;
	string s;

	start = new nodeNine(sm);
	start->gv = 0; // cost so far is 0
	open.push_heap(start);

	getstring(sm, s);
	close.insert(s);

	string temp[sizeNine][sizeNine];
	int success = 0;

	long gencount = 1;

	while (!open.heap_empty() && !success)
	{
		open.pop_heap(current);
		getstring(current->m, s);
		if (s == GOAL_NINE)
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
					succ = new nodeNine(temp, current);
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
					succ = new nodeNine(temp, current);
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
					succ = new nodeNine(temp, current);
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
					succ = new nodeNine(temp, current);
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
					succ = new nodeNine(temp, current);
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
					succ = new nodeNine(temp, current);
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
					succ = new nodeNine(temp, current);
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
					succ = new nodeNine(temp, current);
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

void nine::nineMain()
{
	int size = sizeNine;
	string GAME_BOARD[sizeNine][sizeNine];
	NINE_SIZE = size;
	goalNine = GOAL_NINE;
	int halfSize = (NINE_SIZE - 1) / 2;
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
				GOAL_NINE_MATRIX[i][j] = "B";
			}
			for (j; j < size; j++)
			{
				GOAL_NINE_MATRIX[i][j] = "#";
			}
		}
		else if (i == halfSize)
		{
			int j = 0;
			for (j; j < halfSize; j++)
			{
				GOAL_NINE_MATRIX[i][j] = "B";
			}
			GOAL_NINE_MATRIX[i][j] = " ";
			j++;
			for (j; j < size; j++)
			{
				GOAL_NINE_MATRIX[i][j] = "R";
			}
		}
		else if (i > halfSize)
		{
			int j = 0;
			for (j; j < halfSize; j++)
			{
				GOAL_NINE_MATRIX[i][j] = "#";
			}
			for (j; j < size; j++)
			{
				GOAL_NINE_MATRIX[i][j] = "R";
			}
		}
	}
	best(GAME_BOARD);
}

nine::nine()
{
}


nine::~nine()
{
}
