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
#include <set>

// .first = amount of time spent grazing, .second = (.first = arrival, .second = senority)
typedef std::pair<int, std::pair<int, int>> cowinfo;
// .first = actual time that the cow started grazing, .second = cowinfo
typedef std::pair<int, cowinfo> finalcow;

class Compare
{
public:
	bool operator() (cowinfo c1, cowinfo c2)
	{
		return c1.second > c2.second;
	}
};

class CompareWaiting
{
public:
	bool operator() (cowinfo c1, cowinfo c2)
	{
		// cmp senorities from smallest to largest
		return c1.second.second < c2.second.second;
	}
};

// num of cows
int n;
// pair is t (amount of time eating grass) & a pair--(a -starting time of grass eating, senority)
std::priority_queue<cowinfo, Compare> orig_cows;

std::priority_queue<finalcow, CompareWaiting> waiting_cows;

finalcow final_order[];


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
		orig_cows.push(input);
	}

	int curtime = orig_cows.top.first.first;

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}