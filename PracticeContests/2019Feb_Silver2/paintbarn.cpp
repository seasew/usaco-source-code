/*
ID: alina.l1
LANG: C++
PROB: paintbarn
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

int barn[1000][1000];

int main()
{
	// Open Streams
	std::ifstream fin("paintbarn.in");

	std::ofstream fout("paintbarn.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read File 
	int n;
	int k;
	fin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		int x1, y1, x2, y2;
		fin >> x1 >> y1 >> x2 >> y2;
		
			barn[x1][y1]++;
			barn[x2][y1]++;
			barn[x1][y2]--;
			barn[x2][y2]--;
	}

	int x = 0;
	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			// if i is not zero
			if (i > 0)
			{
				barn[i][j] += barn[i - 1][j];
			}
			// if j is not zero
			if (j > 0)
			{
				barn[i][j] += barn[i][j - 1];
			}
			// if both are not zero
			if (i > 0 && j > 0)
			{
				barn[i][j] -= barn[i - 1][j - 1];
			}

			// check
			if (barn[i][j] == k)
			{
				x++;
			}
		}
	}

	// Write to File
	fout << x << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}