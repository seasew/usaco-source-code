/*
ID: alina.l1
LANG: C++
PROB: milk
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

struct farmer
{
	int p;
	int a
};

bool fCmp(farmer a, farmer b)
{
	if (a.a < b.a)
	{
		return true;
	}
	return false;
}

int main()
{
	// Open Streams
	std::ifstream fin("milk.in");

	std::ofstream fout("milk.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read File
	int n;
	int m;

	fin >> n >> m;

	std::vector<farmer> f;
	for (int i = 0; i < m; i++)
	{
		int p;
		int a;
		fin >> p >> a;
		f.push_back(farmer{ p, a });
	}

	std::sort(f.begin(), f.end(), fCmp());

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}