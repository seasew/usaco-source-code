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

void chooseCows(int startIndex)
{

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


	// Close Streams
	fin.close();
	fout.close();

	return 0;
}