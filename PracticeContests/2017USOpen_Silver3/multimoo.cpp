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

// key = the region ID; val = pair(region size, region value)
std::map<int, std::pair<int, int>> regions;

// key = regID, val = .first: set of adjacent reg IDs, .second: bool if visited
std::map<int, std::set<int>> graph;

// edges of graph (key = regid, val = 
std::map<int, std::vector<bool>> edges;

int cursize;

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
	regions[regionID].first++;

	// call for 4 directions
	for (int a = 0; a < 4; a++)
	{
		int newi = i + deltai[a];
		int newj = j + deltaj[a];

		position newpos = std::make_pair(newi, newj);
		dfs(newpos, target, regionID);
	}
}

// visits regid and calls visitreg for all unvisited adjacent regions
void visitreg(int id1, int id2, int t1, int t2)
{
	// basic checks
	// edge already visited?
	if (edges[id1].at(id2))
	{
		return;
	}

	// does id2 match the targets
	if (regions[id2].second == t1 && regions[id2].second == t2)
	{
		return;
	}

	// update the edge
	(edges[id1])[id2] = true;
	(edges[id2])[id1] = true;

	// update cursize with id2's region size
	cursize += regions[id2].first;
	
	// look for adjacent regions to id2
	for (int newreg : graph[id2])
	{
		visitreg(id2, newreg, t1, t2);
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
				// create a new region in regions map (the pair at the end is 0=regionsize, grid[][]=gridvalue)
				regions.emplace(std::make_pair(curID, std::make_pair(0, grid[pos.first][pos.second])));

				// call dfs
				dfs(pos, grid[i][j], curID);
				// cmp new region size with max1
				int regsize = regions[curID].first;
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
				if (newpos.first >= 0 && newpos.first < n && newpos.second >= 0 && newpos.second < n && regID != gridID[newpos])
				{
					// insert adj reg id
					graph[regID].insert(gridID[newpos]);
					// update bool vector in edges as well (default val is false)
					edges[regID].push_back(false);
				}
			}
		}
	}

	// for each region
	for (int id = 0; id < curID; id++)
	{
		int gridval = regions[id].second;
		// for each of the adjacent edges
		for (int adjreg : graph[id])
		{
			// set to region1's region size
			cursize = regions[id].first;
			// call visitreg (id, id2, t1, t2) for all edges
			visitreg(id, adjreg, gridval, regions[adjreg].second);

			// cmp cursize with max2
			max2 = std::max(max2, cursize);
		}

	}

	// write to file
	fout << max1 << "\n" << max2 << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}