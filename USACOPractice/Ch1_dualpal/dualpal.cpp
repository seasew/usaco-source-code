/*
ID: alina.l1
LANG: C++
PROB: dualpal
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

std::vector<int> conB(int b, int n)
{
	int q;
	bool isFirst = true;

	std::vector<int> out;

	while (isFirst || q != 0)
	{
		isFirst = false;
		q = n / b;

		int curR = n % b;

		out.push_back(curR);

		n = q;
	}

	return out;
}

int main()
{
	// Open Streams
	std::ifstream fin("dualpal.in");

	std::ofstream fout("dualpal.out");

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
	int s;

	// read n
	const int MAX_LENGTH = 100;
	char str[MAX_LENGTH];
	fin.getline(&(str[0]), MAX_LENGTH, ' ');
	n = charArrToInt(str);

	// read s
	fin.getline(&(str[0]), MAX_LENGTH);
	s = charArrToInt(str);
	
	// declare constants for base min(inclusive) and max(exclusive)
	const int bS = 2;
	const int bE = 11;
	s++;
	while (n > 0)
	{
		int bCount = 0;
		// check the current number (s)
		// check all the possible bases
		for (int b = bS; b < bE; b++)
		{
			// convert
			std::vector<int> conversion = conB(b, s);

			// check if conversion isPal
			bool isPal = true;
			for (int i = 0; i < conversion.size(); i++)
			{
				if (conversion.at(i) != conversion.at(conversion.size() - i - 1))
				{
					isPal = false;
					break;
				}
			}

			if (isPal)
			{
				bCount++;
				// if this number has two bases where it is a pal
				if (bCount >= 2)
				{
					// update the number
					n--;
					// print the number
					fout << s << "\n";
					break;
				} 
			}
		}

		// NEXT NUMBER
		s++;
	}

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}