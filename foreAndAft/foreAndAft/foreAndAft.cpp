//
//Fore and Aft (Homework 3)
//By Kade Walter
//CS 438
//Due Date: 2/22/2018 at 12:30 pm
//

#include "stdafx.h"
#include "five.h"
#include "seven.h"
#include "nine.h"
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

int main()
{
	five f;
	seven s;
	nine n;
	el e;
	bool playing = true;
	while (playing)
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
				f.fiveMain();
				playing = true;
			}
			else if (size == 7)
			{
				s.sevenMain();
				playing = true;
			}
			else if (size == 9)
			{
				n.nineMain();
				playing = true;
			}
			else if (size == 11)
			{
				//e.elMain();
				playing = true;
			}
			else
			{
				cout << "Invalid board size. Please try again." << endl;
			}
		}
	}
	return 0;
}