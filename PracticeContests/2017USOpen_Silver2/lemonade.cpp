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

typedef long long int wll;
int n;

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

	wll* arr = new wll[1000000000];

	int count = 0;
	int curi = 0;

	// read file
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		fin >> arr[i];
	}

	// sort the array in descending order
	std::sort(std::begin(arr), std::begin(arr) + n, std::greater<wll>());

	// for each value
	while (curi < n)
	{
		// if count is at most the max num of cows for i
		if (arr[curi] >= count)
		{
			count++;
			curi++;
		}
		else
		{
			// done
			fout << count << "\n";
			break;
		}
	}

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}