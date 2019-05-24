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
// array of x values (starts at index 0)
int x_arr[100002];
// y values
int y_arr[100002];

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
		fin >> x_arr[i] >> y_arr[i];
	}

	// output starts at n
	int out = n;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			fout << x_arr[i] << ", " << y_arr[i] << " - " << x_arr[j] << ", " << y_arr[j] << "\n";
		}
	}

	// write to file

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}