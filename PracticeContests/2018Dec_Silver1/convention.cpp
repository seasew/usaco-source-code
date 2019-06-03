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

// positive int representing the max time if using time 'time'
// otherwise negative int meaning time 'time' is not possible to use
int doesTWork(int time)
{
	int maxWait = 0;

	int curBus = 0;
	int curCows = 0;
	int curBusStartTime = cows_st[0];
	// for each cow
	for (int i = 0; i < n; i++)
	{
		// new bus needed?
		if (curCows >= c)
		{
			// calculate the wait time for the first cow of this bus
			maxWait = std::max(maxWait, curBusStartTime);

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
				// calculate the wait time for the first cow of this bus
				maxWait = std::max(maxWait, curBusStartTime);

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
		return -1;
	}
	return maxWait;
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
	int tPossible;
	int startI = 0;
	int endI = n - 1;
	bool continueT = true;
	while (continueT)
	{
		int curI = (startI + endI) / 2;
		tPossible = doesTWork(cows_st[curI]);

		// is this the smallest possible time T?
		// check if the search should continue
		if (tPossible >= 0)
		{
			// do not continue if the currentPoint is possible, but (curPt - 1) is not possible
			if (curI != 0 && doesTWork(cows_st[curI - 1]) < 0)
			{
				continueT = false;
				break;
			}
			// or, current point is index 0
			else if (curI == 0)
			{
				continueT = false;
				break;
			}
		}

		// update startPt and endPt based on tPossible
		if (tPossible >= 0)
		{
			// decrease value
			endI = curI;
		}
		else
		{
			// increase value
			startI = curI;
		}
	}

	fout << tPossible << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}