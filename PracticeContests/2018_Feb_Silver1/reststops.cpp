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
int origxmeters[1000000];
int origctastiness[1000000];
int xmeters[1000000];
int ctastiness[1000000];

// sort xmeters arr by their tastiness values
bool cmpxmRS(const int xm1, const int xm2)
{
	return ctastiness[xm1] > ctastiness[xm2];
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
		int a, b;
		fin >> a >> b;
		ctastiness[i] = b;
		xmeters[i] = a;

		origctastiness[i] = b;
		origxmeters[i] = a;
	}

	// sort by tastiness
	std::sort(std::begin(xmeters), std::begin(xmeters) + n, cmpxmRS);
	std::sort(std::begin(ctastiness), std::begin(ctastiness) + n, std::greater<int>());

	// 'walk through' ctastiness array 
	int prevI = 0;
	int t = (xmeters[prevI]) * (rf - rb) * (ctastiness[prevI]);
	for (int i = 1; i < n; i++)
	{
		// if the next tastiest RS is after the prev RS
		if (xmeters[i] > xmeters[prevI])
		{
			// this is Bessie's next rest stop
			t += (xmeters[i] - xmeters[prevI]) * (rf - rb) * (ctastiness[i]);
			// update prevI
			prevI = i;
		}

		// otherwise, continue searching for a RS
	}

	fout << t << "\n";

	// close streams
	fin.close();
	fout.close();

	return 0;
}