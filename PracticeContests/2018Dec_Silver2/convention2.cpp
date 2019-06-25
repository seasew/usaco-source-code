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


bool Compare(cowinfo c1, cowinfo c2)
{
	return c1.second > c2.second;
}

bool CompareWaiting(cowinfo c1, cowinfo c2)
{
	// cmp senorities from smallest to largest
	return c1.second.second < c2.second.second;
}

// num of cows
int n;
// pair is t (amount of time eating grass) & a pair--(a -starting time of grass eating, senority)
std::priority_queue<cowinfo, std::vector<cowinfo>, decltype(&Compare)> orig_cows(Compare);
std::priority_queue<cowinfo, std::vector<cowinfo>, decltype(&CompareWaiting)> waiting_cows(CompareWaiting);

finalcow final_order[100000];


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

	// set curtime to the arrival time of the 1st cow
	int curtime = orig_cows.top.second.first;
	int index = 0;
	while (!orig_cows.empty)
	{
		cowinfo processcow;
		// if there are no waiting cows
		// process the next cow in orig_cows
		if (waiting_cows.empty)
		{
			processcow = orig_cows.top;
			orig_cows.pop;
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
			processcow = waiting_cows.top;
			waiting_cows.pop;
			// add the processcow to the final order
			finalcow topfinalcow = std::make_pair(curtime, processcow);
			final_order[index] = topfinalcow;
		}

		// add all the new waiting cows to waiting_cows
		// if the cow's arrival time is >=starttime and <=curtime, then it is now waiting
		int starttime = curtime;
		// update curtime
		curtime += processcow.first;

		while (!orig_cows.empty && orig_cows.top.first.first >= starttime && orig_cows.top.first.first <= curtime)
		{
			// then orig_cows.top is a waiting_cow now
			waiting_cows.push(orig_cows.top);
			orig_cows.pop;
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