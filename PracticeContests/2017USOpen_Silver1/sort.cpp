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
std::list<int> arr;
std::list<int> sorted;

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
		arr.push_back(val);
	}

	// sort
	std::copy(arr.begin(), arr.end(), sorted.begin());
	sorted.sort();

	// for each value in the original array
	int maxdist = 0;
	int count = 0;
	for (int val : arr)
	{
		// find val in the sorted arr
		auto it = std::find(sorted.begin(), sorted.end(), val);

		// find the difference 
		int indexinsorted = std::distance(sorted.begin(), it);
		int diff = std::abs(indexinsorted - count);
		maxdist = std::max(maxdist, diff);
		count++;
	}

	// write to file
	fout << maxdist;

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}