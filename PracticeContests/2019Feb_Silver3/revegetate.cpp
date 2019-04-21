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
int k;
// if cannot find a solution
bool impossible;
// an array of arrays refering to each pastures' same pastures
std::vector<int> same[1000001];
// an array of arrays referring to each pastures' different pastures
std::vector<int> diff[100001];
// values of 0 if not visted yet, 1 or 2
int pastures[100001];

// visits the pasture with the value
void visit(int p, int v)
{
	pastures[p] = v;
	// for each same pasture
	for (int sameP : same[p])
	{
		// if it has already been visited
		if (pastures[sameP])
		{
			// check for consistency
			if (pastures[sameP] != v)
			{
				impossible = true;
				return;
			}
		}
		// if has not been visited
		else
		{
			visit(sameP, v);
		}
	}

	// for each different pasture
	for (int diffP : diff[p])
	{
		// if it has already been visited
		if (pastures[diffP])
		{
			// check for consistency
			if (pastures[diffP] == v)
			{
				impossible = true;
				return;
			}
		}
		// if has not been visted
		else
		{
			// visit it
			visit(diffP, 3 - v);
		}
	}
}

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
			same[p1].push_back(p2);
			same[p2].push_back(p1);
		}
		else
		{
			// diff array
			diff[p1].push_back(p2);
			diff[p2].push_back(p1);
		}
	}

	// for each pasture that hasn't been visited
	for (int i = 1; i <= n; i++)
	{
		if (!pastures[i])
		{
			// visit pasture 1 with grass1
			visit(i, 1);
			k++;
		}
	}

	// if any part of the solution was marked impossible
	if (impossible)
	{
		fout << "0\n";
	}
	else
	{
		fout << "1";
		for (int i = 0; i < k; i++)
		{
			fout << "0";
		}
		fout << "\n";
	}

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}