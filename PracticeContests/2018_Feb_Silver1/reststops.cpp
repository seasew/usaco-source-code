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

int l;
int n;
int rf;
int rb;
int xmeters[1000000];
int ctastiness[1000000];

// sort xmeters arr by their tastiness values
bool cmpxmRS(const int xm1, const int xm2)
{
	return ctastiness[xm1] < ctastiness[xm2];
}

int main()
{
	// open streams
	std::ifstream fin("reststops.in");

	std::ofstream fout("reststops.out");

	// check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// read file
	fin >> l >> n >> rf >> rb;
	for (int i = 0; i < n; i++)
	{
		fin >> xmeters[i] >> ctastiness[i];
	}

	// sort by tastiness
	std::sort(std::begin(xmeters), std::end(xmeters), cmpxmRS);
	std::sort(std::begin(ctastiness), std::end(ctastiness));

	// close streams
	fin.close();
	fout.close();

	return 0;
}