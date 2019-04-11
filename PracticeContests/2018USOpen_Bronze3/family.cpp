/*
ID: alina.l1
LANG: C++
PROB: family
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

int getPast(std::string children[], std::string mothers[], std::string oC, std::string yC, std::string yM, std::string *begin, std::string *end)
{
	if (yM != "not found")
	{
		// check (mother, grandmother, great-grandmother, etc.)
		for (int i = 0; i < 2; i++)
		{
			int mCount = 1;

			bool works = false;

			auto it = std::find(begin, end, yM);
			// while we keep finding yM a mother
			while (it != end)
			{
				// update count
				mCount++;

				std::string nextM = mothers[it - end];
				// if nextM matches old Cow
				if (nextM == oC)
				{
					// It Works!
					works = true;
					break;
				}

				// update yM and yC
				yC = yM;
				yM = nextM;

				it = std::find(begin, end, yM);
			}

			if (works)
			{
				return mCount;
			}
		}
		return -1;
	}
	return -2;
}

int main()
{
	// Open Streams
	std::ifstream fin("family.in");

	std::ofstream fout("family.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	const int MAX_N = 100;
	int n;
	std::string c1;
	std::string c2;

	fin >> n >> c1 >> c2;

	std::string mothers[MAX_N];
	std::string children[MAX_N];

	// read the next n lines
	for (int i = 0; i < n; i++)
	{
		fin >> mothers[i] >> children[i];
	}

	// Check Siblings
	// check children array for c1 and c2
	std::string m1 = "not found";
	std::string m2 = "not found";

	for (int i = 0; i < n; i++)
	{
		if (children[i] == c1)
		{
			m1 = mothers[i];
		}
		if (children[i] == c2)
		{
			m2 = mothers[i];
		}
	}

	if (!(m1 == "not found" || m2 == "not found") && (m1 == m2))
	{
		fout << "SIBLINGS" << "\n";
		return 0;
	}

	// check (mother, grandmother, great-grandmother, etc.)
	for (int i = 0; i < 2; i++)
	{
		std::string oC;
		std::string yC;
		std::string yM;

		if (i == 0)
		{
			oC = c1;
			yC = c2;
			yM = m2;
		}
		else
		{
			oC = c2;
			yC = c1;
			yM = m1;
		}

		int dd = getPast(children, mothers, oC, yC, yM, std::begin(children), std::end(children));
		if (dd > 0)
		{
			std::string output = "mother";
			if (dd > 1)
			{
				output = "grand-" + output;
				for (int i = 2; i < dd; i++)
				{
					output = "great-" + output;
				}
			}
			fout << oC << " is the " << output << " of " << yC << "\n";
			return 0;
		}
	}

	// check CHILD of MOTHER,GMOTHER,GGMOTHER,ETC.
	// first, check with c1's mom (m1) & c2 to see if they are ancestors
	if (m1 != "not found" && m2 != "not found")
	{
		for (int i = 0; i < 2; i++)
		{
			std::string oC;
			std::string yC;
			std::string yM;

			if (i == 0)
			{
				oC = m1;
				yC = c2;
				yM = m2;
			}
			else
			{
				oC = m2;
				yC = c1;
				yM = m1;
			}

			int p = getPast(children, mothers, oC, yC, yM, std::begin(children), std::end(children));
			if (p > 0)
			{
				std::string output = "aunt";
				if (p > 1)
				{
					for (int j = 1; j < p; j++)
					{
						output = "great-" + output;
					}
				}

				std::string older;
				if (oC == m1)
				{
					older = c1;
				}
				else
				{
					older = c2;
				}

				fout << older << " is the " << output << " of " << yC << "\n";
				return 0;
			}
		}
	}

	// Check if COUSINS (related at all)


	// Close Streams
	fin.close();
	fout.close();

	return 0;
}