/*
ID: alina.l1
LANG: C++
PROB: friday
*/

#include <iostream>
#include <fstream>
#include <string>

#define FIRST_YR 1900
#define NUM_DAYS_IN_WEEK 7

int charArrToInt(char cStr[])
{
	std::string str(cStr);
	return std::stoi(str);
}

int main()
{
	int nYears = 0;
	int output[7] = {0};

	// Open Streams
	std::ifstream fin("friday.in");

	std::ofstream fout("friday.out");

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
	nYears = charArrToInt(str);

	// keeps track of the day
	int day = 0;
	// For each year
	for (int i = 0; i < nYears; i++)
	{
		// for each month
		for (int j = 1; j <= 12; j++)
		{
			int daysInMonth = 0;

			// 30 days
			if (j == 4 || j == 6 || j == 9 || j == 11)
			{
				daysInMonth = 30;
			}
			else if (j == 2)
			{
				// Feburary
				int curYear = FIRST_YR + i;
				// check if it is a leap year
				if ((curYear % 4 == 0 && curYear % 100 != 0) || (curYear % 400 == 0))
				{
					daysInMonth = 29;
				}
				else
				{
					daysInMonth = 28;
				}
			}
			else
			{
				daysInMonth = 31;
			}

			day += 13;
			output[(day + 1) % NUM_DAYS_IN_WEEK] ++;
			day += daysInMonth - 13;
		}
	}

	// Write to File
	for (int i = 0; i < NUM_DAYS_IN_WEEK; i++)
	{
		fout << output[i];

		if (i != NUM_DAYS_IN_WEEK - 1)
		{
			fout << " ";
		}
		
	}
	fout << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}