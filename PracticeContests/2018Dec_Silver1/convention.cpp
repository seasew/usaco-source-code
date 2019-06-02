/*
ID: alina.l1
LANG: C++
PROB: convention
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

// N cows (<= 100000)
int n;
// M buses (<= 10000)
int m;
// C cows (<= N)
int c;

// array of cow start times
int cows_st[100000];

bool doesTWork(int time)
{
	int curBus = 0;
	int curCows = 0;
	int curBusStartTime = cows_st[0];
	// for each cow
	for (int i = 0; i < n; i++)
	{
		// new bus needed?
		if (curCows >= c)
		{
			// reset
			curBus++;
			curBusStartTime = cows_st[i];
			// count cow i as a current cow
			curCows = 1;
		}
		// continue the current bus
		else if (curCows < c)
		{
			// if the current cow's start time is too big to fit into the current bus' range
			if (cows_st[i] > curBusStartTime + time)
			{
				// new bus needed
				// reset
				curBus++;
				curBusStartTime = cows_st[i];
				// count cow i as a current cow
				curCows = 1;
			}
			// fit the current cow into the current bus
			else
			{
				// update curCows
				curCows++;
			}
		}
	}

	// check if the bus count exceeds m
	if (curBus > m)
	{
		return false;
	}
	return true;
}

int main()
{
	// Open Streams
	std::ifstream fin("convention.in");

	std::ofstream fout("convention.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}


	// read file
	fin >> n >> m >> c;

	for (int i = 0; i < n; i++)
	{
		fin >> cows_st[i];
	}

	// sort the array ascending
	std::sort(cows_st, cows_st + n);

	// binary search
	int startPt = 0;
	int endPt = cows_st[n - 1];
	bool continueT = true;
	while (continueT)
	{
		int curPt = (startPt + endPt) / 2;
		bool tPossible = doesTWork(curPt);
		// update startPt and endPt based on tPossible
		if (tPossible)
		{
			// decrease value
			endPt = curPt;
		}
		else
		{
			// increase value
			startPt = curPt;
		}
	}

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}