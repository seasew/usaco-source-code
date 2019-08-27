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


struct rs
{
	int meters;
	int tastiness;
};


rs reststops[1000000];

// sort xmeters arr by their tastiness values
bool compareRS(rs rs1, rs rs2)
{
	return rs1.tastiness > rs2.tastiness;
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
		rs newrs = { a, b };
		reststops[i] = newrs;
	}

	// sort by tastiness
	std::sort(std::begin(reststops), std::begin(reststops) + n, compareRS);

	// 'walk through' orig array 
	int prevI = 0;
	int t = (reststops[prevI].meters) * (rf - rb) * (reststops[prevI].tastiness);
	for (int i = 1; i < n; i++)
	{
		// if the next tastiest RS is after the prev RS
		if (reststops[i].meters > reststops[prevI].meters)
		{
			// this is Bessie's next rest stop
			t += (reststops[i].meters - reststops[prevI].meters) * (rf - rb) * (reststops[i].tastiness);
			// update prevI
			prevI = i;
		}

		// otherwise, continue searching for a RS
	}

	fout << t - 1 << "\n";

	// close streams
	fin.close();
	fout.close();

	return 0;
}