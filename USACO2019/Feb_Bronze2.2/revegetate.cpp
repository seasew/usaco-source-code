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
#include <math.h>
#include <vector>

int p[100];
int n;
int m;
int m1[150];
int m2[150];

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

	// Read File 
	fin >> n >> m;

	for (int i = 0; i < m; i++)
	{
		fin >> m1[i] >> m2[i];
	}

	p[0] = 1;



	// i is the pasture number
	for (int i = 2; i <= n; i++)
	{
		// find pasture pairs less than number i
		std::vector<int> pp;
		for (int j = 0; j < m; j++)
		{
			if (m1[j] == i && m2[j] < i)
			{
				pp.push_back(p[m2[j] - 1]);
			}
			if (m2[j] == i && m1[j] < i)
			{
				pp.push_back(p[m1[j] - 1]);
			}
		}

		// find the smallest possible grass type
		for (int j = 1; j <= 4; j++)
		{
			// if grass type not found
			if (std::find(pp.begin(), pp.end(), j) == pp.end())
			{
				p[i - 1] = j;
				break;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		fout << p[i];
	}
	fout << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}