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

int n;
int arr[1000000000];

int main()
{
	// Open Streams
	std::ifstream fin("lemonade.in");

	std::ofstream fout("lemonade.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	int count = 0;
	int curi = 0;

	// read file
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		fin >> arr[i];
	}

	// sort the array in descending order


	// Close Streams
	fin.close();
	fout.close();

	return 0;
}