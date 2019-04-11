/*
ID: alina.l1
LANG: C++
PROB: beads
*/

#include <iostream>
#include <fstream>
#include <string>

int charArrToInt(char cStr[])
{
	std::string str(cStr);
	return std::stoi(str);
}

int wrapIndex(int index, int n)
{
	// if the index is positive
	if (index >= 0)
	{
		// simply mod n
		return index % n;
	}

	// while the index is negative
	while (index < 0)
	{
		// keep adding n until it is positive
		index += n;
	}

	return index;
}

bool beadsMatch(char color, char bead)
{
	if (color == 'w' || color == bead || bead == 'w')
	{
		return true;
	}
	return false;
}

char changeColor(char color, char bead)
{
	if (color == 'w' && bead != 'w')
	{
		return bead;
	}

	return color;
}



int main()
{
	// Open Streams
	std::ifstream fin("beads.in");

	std::ofstream fout("beads.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read File

	// read number of beads value
	int n;
	const int MAX_LENGTH = 100;
	char str[MAX_LENGTH];
	fin.getline(&(str[0]), MAX_LENGTH);
	n = charArrToInt(str);

	// read the necklace
	const int MAX_BEADS = 500;
	char necklace[MAX_BEADS];
	fin.getline(&(necklace[0]), MAX_BEADS);

	// record max value
	int max = 0;

	// For each index
	for (int i = 0; i < n; i++)
	{
		// output value
		int value = 0;

		// go the the right (positive)
		// set color to bead at index i
		char color = necklace[i];
		// it starts at index i + 1
		int curIndex = wrapIndex(i + 1, n);

		// while the beads match and curIndex has not exceeded starting index
		while (beadsMatch(color, necklace[curIndex]) && curIndex != i)
		{
			// update color if necessary
			color = changeColor(color, necklace[curIndex]);

			// update curIndex
			curIndex = wrapIndex(curIndex + 1, n);
		}

		// calculate the difference
		if (curIndex <= i)
		{
			value += (n - i) + curIndex;
		}
		else
		{
			value += curIndex - i;
		}

		// go to the left (negative)
		// set color to the bead at index i - 1
		color = necklace[wrapIndex(i - 1, n)];
		// it starts at index i - 2
		curIndex = wrapIndex(i - 2, n);

		// while the beads match and curIndex has not exceeded starting index
		while (beadsMatch(color, necklace[curIndex]) && curIndex != i)
		{
			// update color if necessary
			color = changeColor(color, necklace[curIndex]);

			// update curIndex
			curIndex = wrapIndex(curIndex - 1, n);
		}

		// calculate and add the difference
		if (curIndex >= i)
		{
			value += (n - curIndex - 1) + i;
		}
		else
		{
			value += (i - 1) - curIndex;
		}

		// if the value exceeds n
		if (value > n)
		{
			// set it to n
			value = n;
		}

		// compare with current max value
		if (value > max)
		{
			max = value;
		}

	}

	// Write to File
	fout << max;
	fout << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}