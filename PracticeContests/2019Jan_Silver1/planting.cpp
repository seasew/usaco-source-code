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

int n;
std::vector<int> adjacent[100001];
std::vector<int> nearAdjacent[100001];
int fields[100001];
bool grass[100001];

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

	// Read file
	fin >> n;
	for (int i = 0; i < n - 1; i++)
	{

	}

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}