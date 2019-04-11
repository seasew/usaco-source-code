
/*
ID: alina.l1
LANG: C++
PROB: milk2
*/

#include <iostream>
#include <memory>
#include <fstream>
#include <string>

#define MAX_MILKING_LENGTH 100
#define MAX_N_LENGTH 100

struct Milking
{
	int begin;
	int end;
};

/*
Compare method for comparing two Milkings.
*/
int milkingcompare(const void* v1, const void* v2)
{
	// creates two Milking variables
	Milking *a, *b;
	// cast parameters to Milking type
	a = (Milking*)v1;
	b = (Milking*)v2;

	// compare a and b's begin variable
	if (a->begin > b->begin)
	{
		return 1;
	}
	else if (a->begin < b->begin)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int charArrToInt(char cStr[])
{
	std::string str(cStr);
	return std::stoi(str);
}

int main()
{
	// Open Streams
	std::ifstream fin("milk2.in");

	std::ofstream fout("milk2.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// number of milkings/farmers
	int n;
	// records the first line of the file
	char cStr[MAX_N_LENGTH];
	fin.getline(cStr, MAX_N_LENGTH);
	// convert from char[] to int
	n = charArrToInt(cStr);

	// create array of milkings 
	std::unique_ptr<Milking[]> milkings(new Milking[n]);

	// for each of the next lines
	for (int i = 0; i < n; i++)
	{
		// read the begin and end time
		// store begin time
		cStr[MAX_MILKING_LENGTH];
		fin.getline(cStr, MAX_MILKING_LENGTH, ' ');
		milkings[i].begin = charArrToInt(cStr);


		// store end time
		cStr[MAX_MILKING_LENGTH];
		fin.getline(cStr, MAX_MILKING_LENGTH);
		milkings[i].end = charArrToInt(cStr);
	}

	// sort the array by begin times
	// use milkingCompare method in qsort
	qsort(milkings.get(), n, sizeof(Milking), milkingcompare);

	// initialize variable that will store the final output
	int oneMilkTime = 0;
	int noMilkTime = 0;

	// this variable stores the current range for oneMilkTime
	Milking curRange = milkings[0];

	// this variable stores the current Milking that it is on
	Milking cur;

	// for each milking from index 1 to the last one
	for (int i = 1; i < n; i++)
	{
		cur = milkings[i];
		// if prev's end is less than cur's begin
		// this means there is No Milking happening between them
		if (cur.begin > curRange.end)
		{
			// check that No Milking time is greater than noMilkTime
			if ((cur.begin - curRange.end) > noMilkTime)
			{
				// set noMilkTime to new time
				noMilkTime = cur.begin - curRange.end;
			}

			// record the previous '1 milk' group
			if ((curRange.end - curRange.begin) > oneMilkTime)
			{
				oneMilkTime = curRange.end - curRange.begin;
			}

			// reset curRange to next Milking
			curRange = milkings[i];
		}
		// if prev's end is >= to cur's begin
		// that means the milkings overlap
		else // if (prev.end >= cur.begin)
		{
			// Merge curRange and cur
			// set a new end index: either endIndex or cur's end
			// whichever is greater
			if (cur.end > curRange.end)
			{
				// set curRange end to new end
				curRange.end = cur.end;
			}
		}
	}

	// record the last curRange
	if ((curRange.end - curRange.begin) > oneMilkTime)
	{
		oneMilkTime = curRange.end - curRange.begin;
	}

	// Write output to out file
	fout << oneMilkTime << " " << noMilkTime << "\n";

	return 0;
}