/*
ID: alina.l1
LANG: C++
PROB: planting
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

int n;
std::vector<int> adjacent[100001];
std::vector<int> nearAdjacent[100001];
int fieldArr[100001];
bool grassArr[100001];

int maxgrass;

void plant(int field, int grass)
{
	// both parameters are 1 based
	// update fields array
	fieldArr[field] = grass;

	// update grassArr array with current adjacent grasses
	for (int adjacentF : adjacent[field])
	{
		grassArr[fieldArr[adjacentF]] = true;
	}

	// then update with newly planted one
	grassArr[grass] = true;

	// find adjacent fields that have not been planted yet
	for (int adjacentF : adjacent[field])
	{
		// if zero
		if (!fieldArr[adjacentF])
		{
			// calculate the correct grass
			for (int i = 1; i < 100001; i++)
			{
				if (grassArr[i])
				{
					// plant it with the smallest grass possible
					plant(adjacentF, i);

					// update grassmax
					maxgrass = std::max(maxgrass, i);
				}
			}
		}
	}

}

int main()
{
	// Open Streams
	std::ifstream fin("planting.in");

	std::ofstream fout("planting.out");

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
	for (int i = 0; i < n - 1; i++)
	{
		int a, b;
		fin >> a >> b;
		// add fields adjacent to the field adjacent to it
		nearAdjacent[a].insert(nearAdjacent[a].end(), adjacent[b].begin(), adjacent[b].end());
		nearAdjacent[b].insert(nearAdjacent[b].end(), adjacent[a].begin(), adjacent[a].end());
		// add adjacent field
		adjacent[a].push_back(b);
		adjacent[b].push_back(a);
	}

	maxgrass = 1;
	// plant starting with field 1 on grass 1
	plant(1, 1);

	// write to file
	fout << maxgrass << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}