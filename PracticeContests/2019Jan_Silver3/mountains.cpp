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
// array of difference values (starts at index 0)
int darr[100002];
// array of sum values
int sarr[100002];

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
		int x, y;
		fin >> x >> y;
		darr[i] = x - y;
		sarr[i] = x + y;
	}
	
	// check every pair for overlap
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			// check if it overlaps
			// find the larger point
			int maxI;
			int minI;
			if (y_arr[i] >= y_arr[j])
			{
				maxI = i;
				minI = j;
			}
			else
			{
				maxI = j;
				minI = i;
			}

			// is the lower point on the left of the larger point?
			if (x_arr[minI] <= x_arr[maxI])
			{
				// subtract and compare
				if ((x_arr[maxI] - x_arr[minI]) <= (y_arr[maxI] - y_arr[minI]))
				{
					// then it overlaps!
					hasoverlap[minI] = true;
				}
			}
			// on the right.
			else
			{
				// subtract and compare
				if (abs(x_arr[minI] - x_arr[maxI]) <= (y_arr[maxI] - y_arr[minI]))
				{
					// then it overlaps!
					hasoverlap[minI] = true;
				}
			}
		}
	}

	int out = 0;
	// Find the number of points with true value (meaning they never had overlap)
	for (int i = 0; i < n; i++)
	{
		if (!hasoverlap[i])
		{
			out++;
		}
	}

	// write to file
	fout << out << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}