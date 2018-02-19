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

//possible goalFive solutions
const string GOAL_ELEVEN = "BBBBBB#####BBBBBB#####BBBBBB#####BBBBBB#####BBBBBB#####BBBBB0RRRRR#####RRRRRR#####RRRRRR#####RRRRRR#####RRRRRR#####RRRRRR";

int ELEVEN_SIZE;
string goalEleven;
string GOAL_ELEVEN_MATRIX[sizeEle][sizeEle];


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
	return ((n1->fv) >(n2->fv));
}

void el::getstring(string m[][sizeEle], string &s1)
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

void el::print1puzzle(ostream &out, string m[][sizeEle])
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

void el::copy(string m[][sizeEle], string n[][sizeEle])
{
	for (int r = 0; r < ELEVEN_SIZE; r++)
		for (int c = 0; c < ELEVEN_SIZE; c++)
			n[r][c] = m[r][c];
}

void el::getposition(string m[][sizeEle], string value, int &row, int &column)
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

int el::up(string m[][sizeEle], string n[][sizeEle])
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

int el::jumpUp(string m[][sizeEle], string n[][sizeEle])
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

int el::down(string m[][sizeEle], string n[][sizeEle])
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

int el::jumpDown(string m[][sizeEle], string n[][sizeEle])
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

int el::left(string m[][sizeEle], string n[][sizeEle])
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

int el::jumpLeft(string m[][sizeEle], string n[][sizeEle])
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

int el::right(string m[][sizeEle], string n[][sizeEle])
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

int el::jumpRight(string m[][sizeEle], string n[][sizeEle])
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

float el::h(string m[][sizeEle])
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


void el::best(string sm[][sizeEle])
{

	nodeEleven *start, *el_current, *el_succ;
	nodeheap open;
	set<string> close;
	string s;

	start = new nodeEleven(sm);
	start->gv = 0; // cost so far is 0
	open.push_heap(start);

	getstring(sm, s);
	close.insert(s);

	string temp[sizeEle][sizeEle];
	int success = 0;

	long gencount = 1;

	while (!open.heap_empty() && !success)
	{
		open.pop_heap(el_current);
		getstring(el_current->m, s);
		if (s == GOAL_ELEVEN)
		{
			printsolution(el_current);
			success = 1;
		}
		else // s is not goal
		{
			if (el_current->parent != NULL)
				getstring(el_current->parent->m, s);
			else
				s = "";
			float fv, gv, hv;
			if (up(el_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					el_succ = new nodeEleven(temp, el_current);
					el_succ->hv = h(temp);
					el_succ->gv = (el_current->gv) + 1;
					el_succ->fv = el_succ->hv + el_succ->gv;
					open.push_heap(el_succ);
					gencount++;
				}
			}
			if (right(el_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					el_succ = new nodeEleven(temp, el_current);
					el_succ->hv = hv = h(temp);
					el_succ->gv = gv = (el_current->gv) + 1;
					el_succ->fv = hv + gv;
					open.push_heap(el_succ);
					gencount++;
				}
			}
			if (left(el_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					el_succ = new nodeEleven(temp, el_current);
					el_succ->hv = hv = h(temp);
					el_succ->gv = gv = (el_current->gv) + 1;
					el_succ->fv = hv + gv;
					open.push_heap(el_succ);
					gencount++;
				}
			}
			if (down(el_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					el_succ = new nodeEleven(temp, el_current);
					el_succ->hv = hv = h(temp);
					el_succ->gv = gv = (el_current->gv) + 1;
					el_succ->fv = hv + gv;
					open.push_heap(el_succ);
					gencount++;
				}
			}
			if (jumpUp(el_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					el_succ = new nodeEleven(temp, el_current);
					el_succ->hv = hv = h(temp);
					el_succ->gv = gv = (el_current->gv) + 1;
					el_succ->fv = hv + gv;
					open.push_heap(el_succ);
					gencount++;
				}
			}
			if (jumpRight(el_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					el_succ = new nodeEleven(temp, el_current);
					el_succ->hv = hv = h(temp);
					el_succ->gv = gv = (el_current->gv) + 1;
					el_succ->fv = hv + gv;
					open.push_heap(el_succ);
					gencount++;
				}
			}
			if (jumpLeft(el_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					el_succ = new nodeEleven(temp, el_current);
					el_succ->hv = hv = h(temp);
					el_succ->gv = gv = (el_current->gv) + 1;
					el_succ->fv = hv + gv;
					open.push_heap(el_succ);
					gencount++;
				}
			}
			if (jumpDown(el_current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					el_succ = new nodeEleven(temp, el_current);
					el_succ->hv = hv = h(temp);
					el_succ->gv = gv = (el_current->gv) + 1;
					el_succ->fv = hv + gv;
					open.push_heap(el_succ);
					gencount++;
				}
			}
		}
	}
	cout << gencount << " nodes visted.\n";
}

void el::elMain()
{
	int size = 11;
	string GAME_BOARD[sizeEle][sizeEle];
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


