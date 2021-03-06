//
//Fore and Aft (Homework 3)
//By Kade Walter
//CS 438
//Due Date: 2/22/2018 at 12:30 pm
//
//This program implements the fore&aft puzzle. It solves it using a manhattan distance algorithm.
//Works for all sizes (5, 7, 9, and 11)
//

#include "stdafx.h"
#include "heap.h"

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

//possible goals
const string goalFive = "BBB##BBB##BB0RR##RRR##RRR";
const string goalSeven = "BBBB###BBBB###BBBB###BBB0RRR###RRRR###RRRR###RRRR";
const string goalNine = "BBBBB####BBBBB####BBBBB####BBBBB####BBBB0RRRR####RRRRR####RRRRR####RRRRR####RRRRR";
const string goalEleven = "BBBBBB#####BBBBBB#####BBBBBB#####BBBBBB#####BBBBBB#####BBBBB0RRRRR#####RRRRRR#####RRRRRR#####RRRRRR#####RRRRRR#####RRRRRR";

int SIZE;
string GOAL;
const int gameboard_size = 11;

struct node
{
	string m[gameboard_size][gameboard_size];
	float hv, gv, fv; // values of h, g, f functions
	node *parent;
	node *next;
	node(string sm[][gameboard_size], node* p = 0, node* n = 0)
	{
		for (int r = 0; r<SIZE; r++)
			for (int c = 0; c<SIZE; c++)
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

int le(node *n1, node *n2)
{
	return ((n1->fv) >(n2->fv));
}

void getstring(string m[][gameboard_size], string &s1)
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

void print1puzzle(ostream &out, string m[][gameboard_size])
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

void printsolution(node* n)
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

void swap(string &a, string &b)
{
	string tmp = a;
	a = b;
	b = tmp;
}

void copy(string m[][gameboard_size], string n[][gameboard_size])
{
	for (int r = 0; r < SIZE; r++)
		for (int c = 0; c < SIZE; c++)
			n[r][c] = m[r][c];
}

void getposition(string m[][gameboard_size], string value, int &row, int &column)
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

bool isSafe(string m[][gameboard_size], int i, int j)
{
	int halfSize = (SIZE - 1) / 2;
	if (i >= 0 && i < SIZE && j >= 0 && j < SIZE)
	{
		if (m[i][j] == "#")
			return false;
		return true;
	}
	else
		return false;
}

int up(string m[][gameboard_size], string n[][gameboard_size])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(m, r0 - 1, c0))
	{
		swap(n[r0][c0], n[r0 - 1][c0]);
		return 1;
	}
	else
		return 0;
}

int jumpUp(string m[][gameboard_size], string n[][gameboard_size])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(m, r0 - 2, c0))
	{
		swap(n[r0][c0], n[r0 - 2][c0]);
		return 1;
	}
	else
		return 0;
}

int down(string m[][gameboard_size], string n[][gameboard_size])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(m, r0 + 1, c0))
	{
		swap(n[r0][c0], n[r0 + 1][c0]);
		return 1;
	}
	else
		return 0;
}

int jumpDown(string m[][gameboard_size], string n[][gameboard_size])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(m, r0 + 2, c0))
	{
		swap(n[r0][c0], n[r0 + 2][c0]);
		return 1;
	}
	else
		return 0;
}

int left(string m[][gameboard_size], string n[][gameboard_size])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(m, r0, c0 - 1))
	{
		swap(n[r0][c0], n[r0][c0 - 1]);
		return 1;
	}
	else
		return 0;
}

int jumpLeft(string m[][gameboard_size], string n[][gameboard_size])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(m, r0, c0 - 2))
	{
		swap(n[r0][c0], n[r0][c0 - 2]);
		return 1;
	}
	else
		return 0;
}

int right(string m[][gameboard_size], string n[][gameboard_size])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(m, r0, c0 + 1))
	{
		swap(n[r0][c0], n[r0][c0 + 1]);
		return 1;
	}
	else
		return 0;
}

int jumpRight(string m[][gameboard_size], string n[][gameboard_size])
{
	int r0, c0;
	copy(m, n);
	getposition(m, " ", r0, c0);

	if (isSafe(m, r0, c0 + 2))
	{
		swap(n[r0][c0], n[r0][c0 + 2]);
		return 1;
	}
	else
		return 0;
}

void blueGoal(int &row, int &col)
{
	int i;
	int j;
	int r = 0, c = 0;
	int value;
	int totalValue = 0;
	int halfSize = (SIZE - 1) / 2;
	for (i = 0; i <= halfSize; i++)
	{
		for (j = 0; j <= halfSize; j++)
		{
			r += i;
			c += j;
		}
	}
	//remove the empty space in the middle of the game board
	r - i;
	c - j;
	row = r; col = c;
}

void redGoal(int &row, int &col)
{
	int i;
	int j;
	int r = 0, c = 0;
	int value;
	int totalValue = 0;
	int halfSize = (SIZE - 1) / 2;
	for (i = halfSize; i < SIZE; i++)
	{
		for (j = halfSize; j < SIZE; j++)
		{
			r += i;
			c += j;
		}
	}
	//remove the empty space in the middle of the game board
	r - halfSize;
	c - halfSize;
	row = r; col = c;
}

void blueTotal(string m[][gameboard_size], int &row, int &col)
{
	int r = 0, c = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (m[i][j] == "B")
			{
				r += i;
				c += j;
			}
		}
	}
	row = r; col = c;
}

void redTotal(string m[][gameboard_size], int &row, int &col)
{
	int r = 0, c = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (m[i][j] == "R")
			{
				r += i;
				c += j;
			}
		}
	}
	row = r; col = c;
}

int distance(int rowGoal, int row, int colGoal, int col)
{
	return abs(rowGoal - row) + abs(colGoal - col);
}

// f(n) = g(n) + C*H2(n)
float C = 5.0;

float h(string m[][gameboard_size])
{
	int total_distance, red_distance, blue_distance;
	//get the total goal locations of blue pieces
	int blueRowGoal, blueColGoal;
	blueGoal(blueRowGoal, blueColGoal);
	//get the total of the row and columns for current boards blue pieces
	int blueRowCurr, blueColCurr;
	blueTotal(m, blueRowCurr, blueColCurr);
	//get the total blue distance
	blue_distance = distance(blueRowGoal, blueRowCurr, blueColGoal, blueColCurr);

	//get the total goal locations of blue pieces
	int redRowGoal, redColGoal;
	redGoal(redRowGoal, redColGoal);
	//get the total of the row and columns for current boards blue pieces
	int redRowCurr, redColCurr;
	redTotal(m, redRowCurr, redColCurr);
	//get the total blue distance
	red_distance = distance(redRowGoal, redRowCurr, redColGoal, redColCurr);

	//get the total distance of blue and red pieces
	total_distance = red_distance + blue_distance;

	return C * total_distance;

}


void best(string sm[][gameboard_size])
{
	node *start, *current, *succ;
	nodeheap open;
	set<string> close;
	string s;

	start = new node(sm);
	start->gv = 0;
	open.push_heap(start);

	getstring(sm, s);
	close.insert(s);

	string temp[gameboard_size][gameboard_size];
	int success = 0;

	long gencount = 1;

	while (!open.heap_empty() && !success)
	{
		open.pop_heap(current);
		getstring(current->m, s);
		if (s == GOAL)
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
					succ->hv = hv = h(temp);
					succ->gv = gv = (current->gv) + 1;
					succ->fv = hv + gv;
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

int main()
{
	bool playing = true;
	int in = 0;
	while (playing)
	{
		//getting the game size
		int size = 0;
		cout << "What is the puzzle size? (5, 7, 9, or 11)" << endl;
		cout << "Or enter -1 to quit playing.\n" << endl;
		cin >> size;
		if (size == -1)
		{
			playing = false;
			break;
		}
		else if ((size != 5) && (size != 7) && (size != 9) && (size != 11))
		{
			cout << "Invalid board size. Please try again." << endl;
			playing = true;
			break;
		}
		else
		{
			SIZE = size;
			//assigning goals
			if (SIZE == 5)
				GOAL = goalFive;
			else if (SIZE == 7)
				GOAL = goalSeven;
			else if (SIZE == 9)
				GOAL = goalNine;
			else if (SIZE == 11)
				GOAL = goalEleven;
			//creating the gameboard
			string GAME_BOARD[gameboard_size][gameboard_size];
			int halfSize = (SIZE - 1) / 2;
			for (int i = 0; i < SIZE; i++)
			{
				if (i < halfSize)
				{
					int j = 0;
					for (j; j <= halfSize; j++)
					{
						GAME_BOARD[i][j] = "R";
					}
					for (j; j < SIZE; j++)
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
					for (j; j < SIZE; j++)
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
					for (j; j < SIZE; j++)
					{
						GAME_BOARD[i][j] = "B";
					}
				}
			}
			best(GAME_BOARD);
		}
	}
	return 0;
}