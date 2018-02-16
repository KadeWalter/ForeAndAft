//
//Fore and Aft (Homework 3)
//By Kade Walter
//CS 438
//Due Date: 2/15/2018 at 12:30 pm
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
#include <vector>
#include <queue>
#include <map>

using namespace std;

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

int SIZE;
string goal;
vector<vector<string>> GOAL;



struct node
{
	vector<vector<string>> m;	
	float hv, gv, fv; // values of h, g, f functions
	node *parent;
	node *next;
	node(vector<vector<string>>sm, node* p = 0, node* n = 0)
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
		for (int k = 0; k<heap_size; k++) delete data[k];
	}

};

int le(node *n1, node *n2)
{
	return ((n1->fv) >(n2->fv));
}

void getstring(vector<vector<string>> m , string &s1)
{
	string s;
	for (int r = 0; r<SIZE; r++)
		for (int c = 0; c<SIZE; c++)
		{
			if (m[r][c] == " ")
				s += '0';
			else
				s += m[r][c];
		}
	s1 = s;
}

void print1puzzle(ostream &out, vector<vector<string>> m)
{
	out << setiosflags(ios::fixed | ios::showpoint)
		<< setprecision(2);

	for (int r = 0; r<SIZE; r++)
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

void copy(vector<vector<string>> m, vector<vector<string>> n)
{
	for (int r = 0; r<SIZE; r++)
		for (int c = 0; c<SIZE; c++)
			n[r][c] = m[r][c];
}

void getposition(vector<vector<string>> m, string value, int &row, int &column)
{
	for (int r = 0; r<SIZE; r++)
		for (int c = 0; c<SIZE; c++)
		{
			if (m[r][c] == value)
			{
				row = r; column = c;
			}
		}
}

bool isSafe(int i, int j)
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

int up(vector<vector<string>> m, vector<vector<string>> n)
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

int jumpUp(vector<vector<string>> m, vector<vector<string>> n)
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

int down(vector<vector<string>> m, vector<vector<string>> n)
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

int jumpDown(vector<vector<string>> m, vector<vector<string>> n)
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

int left(vector<vector<string>> m, vector<vector<string>> n)
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

int jumpLeft(vector<vector<string>> m, vector<vector<string>> n)
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

int right(vector<vector<string>> m, vector<vector<string>> n)
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

int jumpRight(vector<vector<string>> m, vector<vector<string>> n)
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


// the Heuristic function first calcualte the total distance of 
// the tiles from their goal position.  The distance between 2 
// positions is the sum of horizontal and vertical distances, 
// also referred to as the city block distance.
// THe function returns the total_distance*C,
// where C is a coefficient that can be adjusted to fine tune the performance.

// When C=1, the function returns the actual total_distance, which is <=
// to the actual number of moves required (i.e., it never overestimate).  
// In other word, the solution will be optimal, if it can be determined in reasonable
// amount of time,  Unfortunately, this does not work with the difficult cases.

// As C increase, the run time decrease, however, the solution steps get worse.
// Setting C=3 seems to found good solutions in reasonable amount of time.

// f(n) = g(n) + C*H2(n)

float C = 5.0;

float h(vector<vector<string>> m)
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


void best(vector<vector<string>> sm)
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

	vector<vector<string>> temp (SIZE, vector<string>(SIZE));
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

int main()
{
		bool playing = true;
		while (playing == true)
		{
			//getting the game size
			int size = 0;
			cout << "What is the puzzle size? (5, 7, 9, or 11)" << endl;
			cout << "Or enter -1 to quit playing." << endl;
			cin >> size;

			if (size == -1)
			{
				playing = false;
				break;
			}
			else
			{
				if (size == 5)
				{
					SIZE = sizeFive;
					goal = goalFive;
				}
				else if (size == 7)
				{
					SIZE = sizeSeven;
					goal = goalSeven;
				}
				else if (size == 9)
				{
					SIZE = sizeNine;
					goal = goalNine;
				}
				else if (size == 11)
				{
					SIZE = sizeEleven;
					goal = goalEleven;
				}
				else
				{
					playing = true;
					cout << "Invalid size. Please try again." << endl;
					break;
				}
				vector<vector<string>> GAME_BOARD(SIZE, vector<string>(SIZE));
				vector<vector<string>> GOAL(SIZE, vector<string>(SIZE));
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
			return 0;
		}

}

