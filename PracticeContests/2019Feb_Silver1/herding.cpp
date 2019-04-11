/*
ID: alina.l1
LANG: C++
PROB: herding
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

int main()
{
	// Open Streams
	std::ifstream fin("herding.in");

	std::ofstream fout("herding.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	int n;
	fin >> n;

	int cows[100000];

	for (int i = 0; i < n; i++)
	{
		int cur;
		fin >> cur;
		cows[i] = cur;

	}

	std::sort(std::begin(cows), std::begin(cows) + n);

	int maxCows = 0;
	int startI = 0;
	int endI = n;

	for (int i = 0; i < n; i++)
	{
		int cutoff = cows[i] + n;
		int curI = i;
		// continue with this section while it is in the range
		while (cows[curI] < cutoff && curI < n)
		{
			curI++;
		}

		// compare maxCows with the number of cows in this section
		if (curI - i > maxCows)
		{
			// if greater, set the new variables
			maxCows = curI - i;
			startI = i;
			endI = curI;
		}
	}

	// how many cows are before the startI & after endI?
	int before = startI;
	int after = n - endI;

	// Is it a special case?
	if ((before == 0 && after == 1) || (before == 1 && after == 0))
	{
		// if the space at the end is one
		if (before == 0 && after == 1 && cows[endI] - cows[endI - 1] == 2)
		{
			fout << 1 << "\n";
		}
		else if (before == 1 && after == 0 && cows[startI] - cows[startI - 1] == 2)
		{
			fout << 1 << "\n";
		}
		else if (cows[endI - 1] - cows[startI] == (n - 2))
		{
			fout << 2 << "\n";
		}
		else
		{
			fout << 1 << "\n";
		}
	}
	else
	{
		fout << (before + after) << "\n";
	}

	// max:
	fout << std::max(cows[n - 2] - cows[0], cows[n - 1] - cows[1]) - (n - 2) << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}