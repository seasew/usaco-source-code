/*
ID: alina.l1
LANG: C++
PROB: starter_code
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <functional>
#include <queue>
#include <utility>
#include <list>

int n;
std::pair<int, int> arr[1000100];
std::pair<int, int> sorted[1000100];

int main()
{
	// Open Streams
	std::ifstream fin("sort.in");

	std::ofstream fout("sort.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// read file
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		int val;
		fin >> val;
		// (value, orig index)
		arr[i] = std::make_pair(val, i);
		sorted[i] = std::make_pair(val, i);
	}

	// sort the indexes
	std::sort(std::begin(sorted), std::begin(sorted) + n);

	// for each value in the sorted array
	int maxdist = 0;
	for (int i = 0; i < n; i++)
	{
		// abs(i - sorted[i].second)

		maxdist = std::max(maxdist, std::abs(i - sorted[i].second));
	}

	// write to file
	fout << maxdist << "\n";

	// TEST
	bool sortedc = false;
	while (!sortedc)
	{
		sortedc = true;
		fout << "moo" << "\n";
		for (int i = 0; i < n - 1; i++)
		{
			if (arr[i + 1].first < arr[i].first)
			{
				std::pair<int, int> temp = arr[i + 1];
				arr[i + 1] = arr[i];
				arr[i] = temp;
				sortedc = false;
			}
		}
	}
	// TEST

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}