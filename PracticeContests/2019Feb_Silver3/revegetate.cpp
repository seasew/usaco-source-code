/*
ID: alina.l1
LANG: C++
PROB: revegetate
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>


int n;
int m;
// if cannot find a solution
bool impossible;
// an array of arrays refering to each pastures' same pastures
std::vector<int> same[1000000];
// an array of arrays referring to each pastures' different pastures
std::vector<int> diff[100000];
// values of 0 if not visted yet, 1 or 2
int pastures[100000];

int main()
{
	// Open Streams
	std::ifstream fin("revegetate.in");

	std::ofstream fout("revegetate.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}
	
	// read file
	fin >> n >> m;
	// for each cow
	for (int i = 0; i < m; i++)
	{
		char c;
		int p1, p2;
		fin >> c >> p1 >> p2;
		if (c == 'S')
		{
			// add the respective pastures to same array
			same[p1 - 1].push_back(p2);
			same[p2 - 1].push_back(p1);
		}
		else
		{
			diff[p1 - 1].push_back(p2);
			diff[p2 - 1].push_back(p1);
		}
	}

	// Write to File
	fout << "";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}