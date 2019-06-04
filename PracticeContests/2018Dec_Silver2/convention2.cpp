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
bool waiting_cows[100050];
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

	return arrivals[i1] < arrivals[i2];
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

	int maxTime = 0;
	int curTime = arrivals[indexes[0]] + times[indexes[0]];
	// look at each of the indexes in order of arrival time
	for (int i = 0; i < n; i++)
	{

	}

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}