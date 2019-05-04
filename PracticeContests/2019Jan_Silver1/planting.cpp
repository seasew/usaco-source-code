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

	// update grassArr array with current adjacent grasses that have already been planted
	for (int adjacentF : adjacent[field])
	{
		if (fieldArr[adjacentF])
		{
			grassArr[fieldArr[adjacentF]] = true;
		}
	}

	// then update with newly planted one
	grassArr[grass] = true;

	// calculate correct grass
	int newGrass;
	for (int i = 1; i < 100001; i++)
	{
		if (!grassArr[i])
		{
			newGrass = i;
			break;
		}
	}

	// find adjacent fields that have not been planted yet
	for (int adjacentF : adjacent[field])
	{
		// if zero
		if (!fieldArr[adjacentF])
		{
			
			// plant it with the smallest grass possible
			plant(adjacentF, newGrass);

			// update grassmax
			maxgrass = std::max(maxgrass, newGrass);
		}
	}

	// find near-adjacent fields that have not been planted yet
	for (int nearAdjacentF : nearAdjacent[field])
	{
		// if zero
		if (!fieldArr[nearAdjacentF])
		{
			// update grassmax
			maxgrass = std::max(maxgrass, newGrass);

			// plant with the smallest true grass
			plant(nearAdjacentF, newGrass);
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
		
		// add adjacent field
		adjacent[a].push_back(b);
		adjacent[b].push_back(a);
	}

	// add the near adjacent fields
	for (int i = 1; i <= n; i++)
	{
		// for all adjacent fields to i
		for (int adjacentF : adjacent[i])
		{
			// use its adjacent fields (!=i) and add to nAdja
			for (int adjacentF2 : adjacent[adjacentF])
			{
				if (adjacentF2 != i)
				{
					nearAdjacent[i].push_back(adjacentF2);
				}
			}
		}
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