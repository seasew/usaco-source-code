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
// the arrival times
int arrivals[100050];
// the time spent grazing (corresponds to the arrivals array
int times[100050];
// true if waiting, false if not (corresponds to the arrivals array)
bool waiting_cows[100050];
// senority array (corresponds to the arrivals array)
int senority[100050];

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


	// Close Streams
	fin.close();
	fout.close();

	return 0;
}