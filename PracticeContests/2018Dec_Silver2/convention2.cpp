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
// the original order of cows (only used to lookup waitingcows by senority)
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
		// set input in orig_cows and sorted_cows
		orig_cows[i] = input;
		sorted_cows[i] = input;
	}

	// sort the sorted_cows ascending
	std::sort(std::begin(sorted_cows), std::begin(sorted_cows) + n);

	// set curtime to the arrival time of the 1st cow
	int finishedtime = sorted_cows[0].first;
	// updated when cows get processed
	int scindex = 0;
	// current max wait time
	int maxtime = 0;
	while (scindex < n)
	{
		// add all the new waiting cows to waiting_cows
		// if the cow's arrival time is >=starttime and <=finishedtime, then it is now waiting
		int starttime = finishedtime;
		// update curtime (add the amount of time spent grazing)
		finishedtime += sorted_cows[scindex].second.second;

		int i = scindex;
		// did the cow at index i arrive while the processed cow was eating?
		while ((i < n) && (sorted_cows[i].first >= starttime) && (sorted_cows[i].first <= finishedtime))
		{
			// then sorted_cows[i] is a waiting_cow now
			// insert its senority
			waiting_cows.insert(sorted_cows[i].second.first);

			i++;
		}

		cowinfo processcow;

		// if there are no waiting cows
		if (waiting_cows.empty())
		{
			// process the next cow in sorted_cows
			processcow = sorted_cows[scindex];

			// reset the curtime to processcow's arrival time 
			finishedtime = processcow.first;
		}

		// if there are waiting cows
		else
		{
			// process the next waiting cow
			// set process cow to corresponding cow in orig_cows
			processcow = orig_cows[*waiting_cows.begin()];
			waiting_cows.erase(waiting_cows.begin());
		}


		// update scindex
		scindex++;

		// now, actually process the cow
		// find the wait time of processcow and cmp with current max
		maxtime = std::max(maxtime, finishedtime - processcow.second.second);
	}

	fout << maxtime << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}