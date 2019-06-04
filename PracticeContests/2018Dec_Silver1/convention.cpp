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

	int curBus = 1;
	int curCows = 0;
	int curBusStartTime = cows_st[0];
	// for each cow
	for (int i = 0; i < n; i++)
	{
		// new bus needed?
		// 1: the number of cows in the current bus exceeds c
		// 2: the ith cow's start time is out of the range of the current bus
		if (curCows >= c || ((curCows < c) && (cows_st[i] > curBusStartTime + time)))
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
			// fit the current cow into the current bus
			// calculate max wait
			maxWait = std::max(maxWait, cows_st[i] - curBusStartTime);

			// update curCows
			curCows++;
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
	int startT = 0;
	int endT = cows_st[n - 1];
	bool continueT = true;
	while (continueT)
	{
		int curT = (startT + endT) / 2;
		tPossible = doesTWork(curT);

		// is this the smallest possible time T?
		// check if the search should continue
		if (tPossible >= 0)
		{
			// do not continue if the currentPoint is possible, but (curPt - 1) is not possible
			if (curT != cows_st[0] && doesTWork(curT - 1) < 0)
			{
				continueT = false;
				break;
			}
			// or, current point is index 0
			else if (curT == cows_st[0])
			{
				continueT = false;
				break;
			}
		}

		// update startPt and endPt based on tPossible
		if (tPossible >= 0)
		{
			// decrease value
			endT = curT;
		}
		else
		{
			// increase value
			startT = curT;
		}
	}

	fout << doesTWork(tPossible) << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}