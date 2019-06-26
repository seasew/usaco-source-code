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

// .first = arrival, .second = (.first = senority, .second = amount of time spent grazing)
typedef std::pair<int, std::pair<int, int>> cowinfo;

// num of cows
int n;
// the original order of cows
cowinfo orig_cows[100000];
// a sorted version of orig_cows (by arrival time, tie-break by senority)
cowinfo sorted_cows[100000];
// std::set that sorts by senority
std::set <int> waiting_cows;

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

		// other is (senority 0-based, amount of time)
		std::pair <int, int> other;
		other = std::make_pair(i, t);

		input = std::make_pair(a, other);
	}

	// set curtime to the arrival time of the 1st cow
	int curtime = orig_cows.begin.second.first;
	int index = 0;
	while (!(orig_cows.empty))
	{
		cowinfo processcow;
		// if there are no waiting cows
		// process the next cow in orig_cows
		if (waiting_cows.empty)
		{
			processcow = orig_cows.begin;
			orig_cows.erase(orig_cows.begin);
			// process the top cow in orig_cows
			// add the top cow to the final order
			// create a finalcow type from the cowinfo of top cow
			finalcow topfinalcow = std::make_pair(curtime, processcow);
			final_order[index] = topfinalcow;
		}
		// if there are waiting cows
		else
		{
			// process the next waiting cow
			processcow = waiting_cows.begin;
			waiting_cows.erase(waiting_cows.begin);
			// add the processcow to the final order
			finalcow topfinalcow = std::make_pair(curtime, processcow);
			final_order[index] = topfinalcow;
		}

		// add all the new waiting cows to waiting_cows
		// if the cow's arrival time is >=starttime and <=curtime, then it is now waiting
		int starttime = curtime;
		// update curtime
		curtime += processcow.first;

		while (!orig_cows.empty && orig_cows.begin.first.first >= starttime && orig_cows.begin.first.first <= curtime)
		{
			// then orig_cows.top is a waiting_cow now
			waiting_cows.insert(orig_cows.begin);
			orig_cows.erase(orig_cows.begin);
		}

		// update index
		index++;
	}

	// find the max waiting time of the cows in final_order
	int max;
	for (int i = 0; i < index; i++)
	{
		max = std::max(max, final_order[i].first - final_order[i].second.second.first);
	}

	fout << max;

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}