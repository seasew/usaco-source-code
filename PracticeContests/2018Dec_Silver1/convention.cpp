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