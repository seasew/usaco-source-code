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
std::pair<int, int> arr[1000000];

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
	}

	// sort the indexes
	std::sort(std::begin(arr), std::end(arr));

	// for each value in the original array
	int maxdist = 0;
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		// set the wanted value
		int arrval = arr.front();

		// find val in the sorted arr
		auto sortedit = std::find(sorted.begin(), sorted.end(), arrval);

		// if value was not found
		if (sortedit == sorted.end())
		{
			break;
		}

		// find the difference 
		int indexinsorted = std::distance(sorted.begin(), sortedit);
		int diff = std::abs(indexinsorted - count);
		maxdist = std::max(maxdist, diff);

		// remove first value in list arr
		arr.pop_front();
		// remove value at iterator it in list sorted
		sorted.erase(sortedit);

		count++;
	}

	// write to file
	fout << maxdist;

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}