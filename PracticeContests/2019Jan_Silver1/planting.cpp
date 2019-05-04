/*
ID: alina.l1
LANG: C++
PROB: planting
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

// field array to hold the number of adjacent fields for each field
int fields[100001];

int main()
{
	// Open Streams
	std::ifstream fin("planting.in");

	std::ofstream fout("planting.out");

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


	for (int i = 1; i < n; i++)
	{
		int a, b;
		fin >> a >> b;
		// increment
		fields[a]++;
		fields[b]++;
	}

	int x = *std::max_element(fields, fields + n);

	fout << (x) + 1 << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}