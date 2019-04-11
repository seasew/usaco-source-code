/*
ID: alina.l1
LANG: C++
PROB: sleepy
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int charArrToInt(char cStr[])
{
	std::string str(cStr);
	return std::stoi(str);
}

int main()
{
	// Open Streams
	std::ifstream fin("sleepy.in");

	std::ofstream fout("sleepy.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read File
	const int MAX_LENGTH = 100;
	char str[MAX_LENGTH];
	fin.getline(&(str[0]), MAX_LENGTH);
	
	int n = charArrToInt(str);

	std::vector<int> seq;

	// record the sequence
	for (int i = 0; i < n; i++)
	{
		fin.getline(&(str[0]), MAX_LENGTH, ' ');
		seq.push_back(charArrToInt(str));
	}

	// the index of the beginning of the sorted part
	int sBeg = n - 1;

	// find the value of sBeg
	for (int i = (n - 1); i > 0; i--)
	{
		// if the current value is NOT greater than previous element
		if (!(seq.at(i) > seq.at(i - 1)))
		{
			// then sBeg ends here
			break;
		}

		sBeg--;
	}

	int out = 0;

	// while there is still more to be sorted
	while (sBeg > 0)
	{
		int first = seq.at(0);
		int last = seq.at(n - 1);

		// if first is less then the all the sorted elements
		if (first < seq.at(sBeg))
		{
			// then first should be moved before the sorted part
			seq.insert(seq.begin() + (sBeg), first);
			
		}
		else if (first > last)
		{
			// move first to the end
			seq.push_back(first);
			
		}
		else // if first is supposed to be somewhere in the sorted part
		{
			// figure out where to move first
			// while the cur index is greater than first and in the sorted region
			int index = n - 1;
			while (index >= sBeg && seq.at(index) > first)
			{
				index--;
			}
			index++;

			// insert the element
			seq.insert(seq.begin() + index, first);
		}

		// erase the first element
		seq.erase(seq.begin());
		// add another element to the sorted part
		sBeg--;
		out++;
	}

	fout << out;

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}