/*
ID: alina.l1
LANG: C++
PROB: milkorder
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

void placeCows(int *order, int n, int *socialH, bool *overlap, int index, int orderI)
{
	// index refers to the TrueCow that we want to look at

	// look at the prev cow in the socialH
	int curI = index - 1;
	orderI--;

	// while curI is still in bounds and the next one is False
	while (curI >= 0 && curI < n && orderI >= 0 && !overlap[curI])
	{
		// put the cow at curI as close to the TrueCow as possible
		while (orderI > 0 && order[orderI] != 0)
		{
			orderI--;
		}

		// in the empty spot, put the cow in from the social order
		order[orderI] = socialH[curI];

		// update curI, look at the next cow
		curI--;
	}
}

int main()
{
	// Open Streams
	std::ifstream fin("milkorder.in");

	std::ofstream fout("milkorder.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read File
	const int maxN = 100;
	int n;
	int m;
	int k;
	// first line
	fin >> n >> m >> k;
	// initalize arrays
	int order[maxN];
	std::fill(std::begin(order), std::begin(order) + n, 0);

	int socialH[maxN];
	bool overlap[maxN];
	std::fill(std::begin(overlap), std::begin(overlap) + m, false);

	// read the m integers (social hierachy)
	for (int i = 0; i < m; i++)
	{
		fin >> socialH[i];
	}

	// read k lines
	for (int i = 0; i < k; i++)
	{
		// read cow number
		int cNum;
		fin >> cNum;
		// read pos (1-based change to 0-based)
		int cPos;
		fin >> cPos;
		cPos--;

		// Check if cow is cow1
		if (cNum == 1)
		{
			// Done!
			fout << (cPos + 1) << "\n";
			return 0;
		}

		// place cow in order
		order[cPos] = cNum;

		// check if the cNum matches with any cow in the socialH
		for (int j = 0; j < m; j++)
		{
			// if matches
			if (socialH[j] == cNum)
			{
				// set corresponding overlap index to true
				overlap[j] = true;
			}
		}
	}

	// check if cow1 is in socialH
	int cow1 = -1;
	for (int i = 0; i < m; i++)
	{
		if (socialH[i] == 1)
		{
			cow1 = i;
			break;
		}
	}

	// if it is
	if (cow1 >= 0)
	{
		int startI = cow1 - 1;
		while (startI >= 0 && !overlap[startI])
		{
			startI--;
		}

		int dist = cow1 - startI;

		int curI;
		if (startI < 0)
		{
			curI = 0;
		}
		else
		{
			curI = (std::find(std::begin(order), std::end(order), socialH[startI]) - std::begin(order));
		}

		for (int i = 0; i < dist; i++)
		{
			while (order[curI] != 0)
			{
				curI++;
			}
			curI++;
		}

		fout << curI << "\n";
		return 0;
	}

	// for each TrueCow in overlap, call the function
	int lastI = 0;
	for (int i = 0; i < m; i++)
	{
		if (overlap[i])
		{
			lastI = i;
			auto it = std::find(std::begin(order), std::end(order), socialH[i]);

			int distance = std::distance(it, std::begin(order) + n);
			if (distance != 0)
			{
				placeCows(order, n, socialH, overlap, i, it - std::begin(order));
			}
		}
	}


	// check if cow1 is in the order
	for (int i = 0; i < n; i++)
	{
		if (order[i] == 1)
		{
			fout << (i + 1) << "\n";
			return 0;
		}
	}

	// Now, we find the earliest empty spot for Cow 1
	int output = 1 + (std::find(std::begin(order), std::end(order), 0) - std::begin(order));
	fout << output << "\n";



	// Close Streams
	fin.close();
	fout.close();

	return 0;
}