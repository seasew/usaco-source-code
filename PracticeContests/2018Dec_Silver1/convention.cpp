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
int cows_st[200000];
// array of adjacent cow differences (size is N-1)
int cows_d[200000];
// array of index beginning of each M bus split (index[0] = 0, etc.) 
int bus_index[20000];
int curBusIndex;

void chooseCows(int startIndex)
{
	if (startIndex < 0 || startIndex >= n)
	{
		return;
	}

	bus_index[curBusIndex] = startIndex;
	curBusIndex++;
	
	int maxEndIndex = 0;
	// if i was the length of the cow busline
	for (int i = 0; i < c; i++)
	{
		// the current index of the end of the bus split (exclusive)
		int endIndex = startIndex + i;

		// if the new difference is greater than the current max diff
		if (cows_d[endIndex] > cows_d[maxEndIndex])
		{
			// assign a new max index
			maxEndIndex = endIndex;
		}
	}

	chooseCows(maxEndIndex);
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

	// the output is the maximum of the difference between first and last in the buses

	bus_index[0] = 0;

	// read file
	fin >> n >> m >> c;

	for (int i = 0; i < n; i++)
	{
		fin >> cows_st[i];
	}

	// sort the array ascending
	std::sort(cows_st, cows_st + n);

	// another array for the differences
	for (int i = 0; i < n - 1; i++)
	{
		cows_d[i] = cows_st[i + 1] - cows_st[i];
	}

	// call chooseCow
	chooseCows(0);

	// Output -- maximum value of (last - first)
	int out = 0;
	for (int i = 0; i < m - 1; i++)
	{
		if (bus_index[i + 1] - bus_index[i] > out)
		{
			out = bus_index[i + 1] - bus_index[i];
		}
	}

	fout << out;

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}