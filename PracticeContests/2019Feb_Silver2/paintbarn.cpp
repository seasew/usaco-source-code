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

int barn[1001][1001];

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
		for (int a = x1; a < x2; a++)
		{
			barn[a][y1]++;
			barn[a][y2]--;
		}
	}

	int x = 0;
	for (int i = 0; i < 10; i++)
	{
		if (barn[i][0] == k)
		{
			x++;
		}

		for (int j = 1; j < 1001; j++)
		{

			barn[i][j] += barn[i][j - 1];
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