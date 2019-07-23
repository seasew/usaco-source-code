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
#include <list>
#include <map>
#include <set>

typedef std::pair<int, int> position;

int deltai[] = {1, 0, -1, 0};
int deltaj[] = {0, 1, 0, -1};

int n;

int max1;
int max2;

// 2d array with the original values of the grid
int grid[250][250];

// key = position (i, j); val = the region ID for that position
std::map<position, int> gridID;

// key = the region ID; val = the positions in that region
std::map<int, std::set<position>> regions;

// key = two adjacent positions; val = if the edge between the two positions has been visited
std::map<std::pair<position, position>, bool> edges;

// searches through grid for target values adjacent to position
// updates cursize
// updates regions
// updates gridID
void dfs(position pos, int target, int regionID)
{
	int i = pos.first;
	int j = pos.second;
	// basic checks
	// pos in bounds?
	if (i < 0 || i >= n || j < 0 || j >= n)
	{
		return;
	}
	// position matches target?
	if (grid[i][j] != target)
	{
		return;
	}
	// is the pos already part of a region? (this means it has been visited)
	if (gridID.at(pos) >= 0)
	{
		return;
	}
}

int main()
{
	// Open Streams
	std::ifstream fin("multimoo.in");

	std::ofstream fout("multimoo.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// read file
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fin >> grid[i][j];
		}
	}

	// 1-cow team code
	// calls recursive method

	// write to file
	fout << max1 << "\n" << max2 << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}