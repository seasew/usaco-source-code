/*
ID: alina.l1
LANG: C++
PROB: convention2
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

// num of cows
int n;
// the sorted indexes (sorted by arrival time)
int indexes[100050];
// the arrival times
int arrivals[100050];
// the time spent grazing 
int times[100050];
// true if waiting, false if not
bool waiting_cows[100050] = { true };
// senority array
int senority[100050];

// method that sorts the indexes based on arrivals
bool cmp(int i1, int i2)
{
	// less than
	if (arrivals[i1] < arrivals[i2])
	{
		return true;
	}
	// greater than
	else if (arrivals[i1] > arrivals[i2])
	{
		return false;
	}
	// equal arrival times
	else
	{
		// compare the senority instead
		// smaller senority comes before
		return senority[i1] < senority[i2];
	}
}

// method that finds the index that is the upper bound of the time
int findBound(int time)
{
	// looks through the arrival times array using binary search
	// find arrivals[i] >= time
	int outI = -1;
	bool found = false;
	int startI = 0;
	int endI = n - 1;
	while (!found)
	{
		int curI = (startI + endI) / 2;

		// check if we need to continue searching
		if ((arrivals[curI] >= time && curI == 0)
			|| (arrivals[curI] >= time && arrivals[curI - 1] < time))
		{
			// this means we don't need to keep searching
			outI = curI;
			found = true;
			break;
		}

		// update the start and end pointers
		if (arrivals[curI] >= time)
		{
			endI = curI;
		}
		else // if arrivals[curI] < time
		{
			startI = curI;
		}
	}

	return outI;
}

int main()
{
	// Open Streams
	std::ifstream fin("convention2.in");

	std::ofstream fout("convention2.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read file
	fin >> n;

	for (int i = 0; i < n; i++)
	{
		fin >> arrivals[i];
		fin >> times[i];
		senority[i] = i + 1;
		indexes[i] = i;
	}

	// sort index array using custom method
	std::sort(indexes, indexes + n, cmp);
	
	int curI = 0;
	int maxTime = 0;
	int curTime = arrivals[indexes[0]];
	waiting_cows[0] = false;
	// n cows will eat
	for (int i = 0; i < n; i++)
	{
		// update curTime
		curTime += times[indexes[curI]];

		int endWaitI;
		// find the upper index bound (exclusive) of the waiting cows
		// cows with arrival times <= curTime
		// call method
		endWaitI = findBound(curTime);
		
		// compare ith cow's waiting time with maxTime
		maxTime = std::max(maxTime, curTime - arrivals[indexes[curI]]);

		// figure out -- which cow should eat next?
		// update curI
		// find the index of the smallest senority in the cows that are waiting
		// find a cow that has true as waiting
		while (!waiting_cows[curI])
		{
			// find the min element until it is true that it is waiting
			curI = std::min_element(senority, senority + endWaitI) - std::begin(senority);
		}
		waiting_cows[curI] = false;
	}

	fout << maxTime << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}