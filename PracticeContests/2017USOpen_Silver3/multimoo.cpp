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

// key = regID, val = .first: set of adjacent reg IDs, .second: bool if visited
std::map<int, std::pair<std::set<int>, bool>> graph;

// searches through grid for target values adjacent to position
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
	
	// update maps
	gridID[pos] = regionID;
	regions[regionID].insert(pos);

	// call for 4 directions
	for (int a = 0; a < 4; a++)
	{
		int newi = i + deltai[a];
		int newj = j + deltaj[a];

		position newpos = std::make_pair(newi, newj);
		dfs(newpos, target, regionID);
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
			// initialize grid array
			fin >> grid[i][j];

			// initalize gridID with all the possible (i, j) & regionID= -1
			position p = std::make_pair(i, j);
			gridID.insert(std::make_pair (p, -1));
			
		}
	}

	// 1-cow team code
	int curID = 0;
	// calls recursive method for every "no region" key
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			position pos = std::make_pair(i, j);
			// if pos does not have a region yet
			if (gridID.at(pos) < 0)
			{
				// create a new region in regions map
				std::set<position> temp;
				regions.emplace(std::make_pair(curID, temp));

				// call dfs
				dfs(pos, grid[i][j], curID);
				// cmp new region size with max1
				int regsize = regions[curID].size();
				max1 = std::max(max1, regsize);

				curID++;
			}
		}
	}
	
	// 2-cow team code
	// create a graph with true-false edges between adjacent regions
	// for each position/value
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			position pos = std::make_pair(i, j);
			int regID = gridID[pos];

			// for each of the four directions
			for (int a = 0; a < 4; a++)
			{
				position newpos = std::make_pair(i + deltai[a], j + deltaj[a]);
				// if they have different regionIDs, add it to the adjacent set of values
				if (regID != gridID[newpos])
				{
					// insert adj reg id
					graph[regID].first.insert(gridID[newpos]);
				}
			}
		}
	}

	// for each region
	for (int id = 0; id < curID; id++)
	{
		visitreg(id);
	}

	// write to file
	fout << max1 << "\n" << max2 << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}