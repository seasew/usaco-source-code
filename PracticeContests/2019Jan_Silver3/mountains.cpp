/*
ID: alina.l1
LANG: C++
PROB: mountains
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

// <= 100000
int n;
// array of points
int xarr[100002];
int yarr[100002];
// array of sorted indexes
int id[100002];

bool cmp(int i1, int i2)
{
	// sort differences ascending

	if ((xarr[i1] - yarr[i1]) < (xarr[i2] - yarr[i2]))
	{
		return true;
	}

	return false;
}

int main()
{
	// Open Streams
	std::ifstream fin("mountains.in");

	std::ofstream fout("mountains.out");

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
		fin >> xarr[i] >> yarr[i];
		id[i] = i;
	}

	// sort indexes using method
	std::sort(id, id + n, cmp);

	// walk through the sorted differences and compare the sums
	int out = 1;
	int maxsum = xarr[id[0]] + yarr[id[0]];
	for (int i = 1; i < n; i++)
	{
		// when the new sum is greater than the current max sum
		if ((xarr[id[i]] + yarr[id[i]]) > maxsum)
		{
			// then there is no overlap
			out++;
			// set the new maxsum
			maxsum = (xarr[id[i]] + yarr[id[i]]);
		}
	}

	// write to file
	fout << out << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}