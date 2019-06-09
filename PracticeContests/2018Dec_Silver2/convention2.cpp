/*
ID: alina.l1
LANG: C++
PROB: convention2
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

// num of cows
int n;
// pair is t (amount of time eating grass) & a pair--(a -starting time of grass eating, senority)
std::priority_queue<std::pair<int, std::pair<int, int>>> arr;

int main()
{
	// Open Streams
	std::ifstream fin("convention2.in");

	std::ofstream fout("convention2.out");

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

	for (int i = 0; i < n; i++)
	{
		// read a, then t
		int a, t;
		fin >> a >> t;
		std::pair <int, std::pair<int, int>> input;
		std::pair <int, int> other;
		other = std::make_pair(a, i);
		input = std::make_pair(t, other);

		// push to priority queue
		arr.push(input);
	}

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}