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


class Compare
{
public:
	bool operator() (std::pair<int, std::pair<int, int>> c1, std::pair<int, std::pair<int, int>> c2)
	{
		return c1.second > c2.second;
	}
};

// num of cows
int n;
// pair is t (amount of time eating grass) & a pair--(a -starting time of grass eating, senority)
std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, Compare> queue;


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
		queue.push(input);
	}

	// walk through the sorted arr and calculate the waiting time for each cow
	int maxtime = 0;
	int curtime = queue.top().second.first;

	std::set<std::pair<int, std::pair<int, int>>, CompareWaiting> waiting_cows;
	for (int i = 0; i < n; i++)
	{
		std::pair<int, std::pair<int, int>> curcow = queue.top();
		int a = (curcow.second).first;
		int t = curcow.first;
		queue.pop();

		// calculate the wait time between curtime and the cow's arrival time
		// cmp to maxtime
		maxtime = std::max(maxtime, curtime - a);

		// add the amount of time this cow needs to graze to curtime
		curtime += t;

		// what range of cows arrived after curcow but before (curcow + a)--> curtime
		while (queue.top().second.first > a && queue.top().second.first <= curtime)
		{
			// add the top to the ordered set
			// pop it off to prepare to check the next cow
		}

		// push the ordered set to the queue
	}

	// output to file
	fout << maxtime;

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}