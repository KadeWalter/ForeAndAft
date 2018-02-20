#include "stdafx.h"
#include "structs.h"
#include "elevenHeap.h"
#include "el.h"

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

//possible goalEleven solutions
const string GOAL_ELEVEN = "BBB##BBB##BB0RR##RRR##RRR";

int ELEVEN_SIZE;
string goalEleven;
string GOAL_ELEVEN_MATRIX[sizeEleven][sizeEleven];


class nodeheap : public heap<nodeEleven *, 100000>
{
public:
	friend int el::le(nodeEleven *n1, nodeEleven *n2);  // less than or equal to
	~nodeheap()
	{
		for (int k = 0; k < heap_size; k++) delete data[k];
	}

};

int el::le(nodeEleven *n1, nodeEleven *n2)
{
	return ((n1->fv) > (n2->fv));
}

void el::getstring(string m[][sizeEleven], string &s1)
{
	string s;
	for (int r = 0; r < ELEVEN_SIZE; r++)
		for (int c = 0; c < ELEVEN_SIZE; c++)
		{
			if (m[r][c] == " ")
				s += '0';
			else
				s += m[r][c];
		}
	s1 = s;
}

void el::print1puzzle(ostream &out, string m[][sizeEleven])
{
	out << setiosflags(ios::fixed | ios::showpoint)
		<< setprecision(2);

	for (int r = 0; r < ELEVEN_SIZE; r++)
	{
		for (int c = 0; c < ELEVEN_SIZE; c++)
			out << m[r][c];
		out << endl;
	}
}

void el::printsolution(nodeEleven* n)
{


	string sizeString = to_string(ELEVEN_SIZE);
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

void el::swap(string &a, string &b)
{
	string tmp = a;
	a = b;
	b = tmp;
}

void el::copy(string m[][sizeEleven], string n[][sizeEleven])
{
	for (int r = 0; r < ELEVEN_SIZE; r++)
		for (int c = 0; c < ELEVEN_SIZE; c++)
			n[r][c] = m[r][c];
}

void el::getposition(string m[][sizeEleven], string value, int &row, int &column)
{
	for (int r = 0; r < ELEVEN_SIZE; r++)
		for (int c = 0; c < ELEVEN_SIZE; c++)
		{
			if (m[r][c] == value)
			{
				row = r; column = c;
			}
		}
}

bool el::isSafe(int i, int j)
{
	int halfSize = (ELEVEN_SIZE - 1) / 2;
	if (i >= 0 && i < ELEVEN_SIZE && j >= 0 && j < ELEVEN_SIZE)
	{
		if (GOAL_ELEVEN_MATRIX[i][j] == "#")
			return false;
		return true;
	}
	else
		return false;
}

int el::up(string m[][sizeEleven], string n[][sizeEleven])
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

int el::jumpUp(string m[][sizeEleven], string n[][sizeEleven])
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

int el::down(string m[][sizeEleven], string n[][sizeEleven])
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

int el::jumpDown(string m[][sizeEleven], string n[][sizeEleven])
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

int el::left(string m[][sizeEleven], string n[][sizeEleven])
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

int el::jumpLeft(string m[][sizeEleven], string n[][sizeEleven])
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

int el::right(string m[][sizeEleven], string n[][sizeEleven])
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

int el::jumpRight(string m[][sizeEleven], string n[][sizeEleven])
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

float EL_C = 5.0;

float el::h(string m[][sizeEleven])
{
	int halfSize = (ELEVEN_SIZE - 1) / 2;
	int goalBlueTotal = 50;
	int currBlueTotal = 0;
	int total_distance = 0;

	for (int i = 0; i < ELEVEN_SIZE; i++)
	{
		for (int j = 0; j < ELEVEN_SIZE; j++)
		{
			if (m[i][j] == "B")
			{
				int temp = (ELEVEN_SIZE * i) + (j + 1);
				currBlueTotal += temp;
			}
		}
	}

	total_distance = currBlueTotal - goalBlueTotal;
	return EL_C * total_distance;

}


void el::best(string sm[][sizeEleven])
{

	nodeEleven *start, *five_current, *five_succ;
	nodeheap open;
	set<string> close;
	string s;

	start = new nodeEleven(sm);
	start->gv = 0; // cost so far is 0
	open.push_heap(start);

	getstring(sm, s);
	close.insert(s);

	string temp[sizeEleven][sizeEleven];
	int success = 0;

	long gencount = 1;

	while (!open.heap_empty() && !success)
	{
		open.pop_heap(five_current);
		getstring(five_current->m, s);
		if (s == GOAL_ELEVEN)
		{
			printsolution(five_current);
			success = 1;
		}
		else // s is not goal
		{
			if (five_current->parent != NULL)
				getstring(five_current->parent->m, s);
			else
				s = "";
			float fv, gv, hv;
			if (up(five_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					five_succ = new nodeEleven(temp, five_current);
					five_succ->hv = h(temp);
					five_succ->gv = (five_current->gv) + 1;
					five_succ->fv = five_succ->hv + five_succ->gv;
					open.push_heap(five_succ);
					gencount++;
				}
			}
			if (right(five_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					five_succ = new nodeEleven(temp, five_current);
					five_succ->hv = hv = h(temp);
					five_succ->gv = gv = (five_current->gv) + 1;
					five_succ->fv = hv + gv;
					open.push_heap(five_succ);
					gencount++;
				}
			}
			if (left(five_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					five_succ = new nodeEleven(temp, five_current);
					five_succ->hv = hv = h(temp);
					five_succ->gv = gv = (five_current->gv) + 1;
					five_succ->fv = hv + gv;
					open.push_heap(five_succ);
					gencount++;
				}
			}
			if (down(five_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					five_succ = new nodeEleven(temp, five_current);
					five_succ->hv = hv = h(temp);
					five_succ->gv = gv = (five_current->gv) + 1;
					five_succ->fv = hv + gv;
					open.push_heap(five_succ);
					gencount++;
				}
			}
			if (jumpUp(five_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					five_succ = new nodeEleven(temp, five_current);
					five_succ->hv = hv = h(temp);
					five_succ->gv = gv = (five_current->gv) + 1;
					five_succ->fv = hv + gv;
					open.push_heap(five_succ);
					gencount++;
				}
			}
			if (jumpRight(five_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					five_succ = new nodeEleven(temp, five_current);
					five_succ->hv = hv = h(temp);
					five_succ->gv = gv = (five_current->gv) + 1;
					five_succ->fv = hv + gv;
					open.push_heap(five_succ);
					gencount++;
				}
			}
			if (jumpLeft(five_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					five_succ = new nodeEleven(temp, five_current);
					five_succ->hv = hv = h(temp);
					five_succ->gv = gv = (five_current->gv) + 1;
					five_succ->fv = hv + gv;
					open.push_heap(five_succ);
					gencount++;
				}
			}
			if (jumpDown(five_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					five_succ = new nodeEleven(temp, five_current);
					five_succ->hv = hv = h(temp);
					five_succ->gv = gv = (five_current->gv) + 1;
					five_succ->fv = hv + gv;
					open.push_heap(five_succ);
					gencount++;
				}
			}
		}
	}
	cout << gencount << " nodes visted.\n";
}

void el::elMain()
{
	int size = 5;
	string GAME_BOARD[sizeEleven][sizeEleven];
	ELEVEN_SIZE = size;
	int halfSize = (ELEVEN_SIZE - 1) / 2;
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
				GOAL_ELEVEN_MATRIX[i][j] = "B";
			}
			for (j; j < size; j++)
			{
				GOAL_ELEVEN_MATRIX[i][j] = "#";
			}
		}
		else if (i == halfSize)
		{
			int j = 0;
			for (j; j < halfSize; j++)
			{
				GOAL_ELEVEN_MATRIX[i][j] = "B";
			}
			GOAL_ELEVEN_MATRIX[i][j] = " ";
			j++;
			for (j; j < size; j++)
			{
				GOAL_ELEVEN_MATRIX[i][j] = "R";
			}
		}
		else if (i > halfSize)
		{
			int j = 0;
			for (j; j < halfSize; j++)
			{
				GOAL_ELEVEN_MATRIX[i][j] = "#";
			}
			for (j; j < size; j++)
			{
				GOAL_ELEVEN_MATRIX[i][j] = "R";
			}
		}
	}
	best(GAME_BOARD);
}


