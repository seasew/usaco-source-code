/*
ID: alina.l1
LANG: C++
PROB: starter_code
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>


struct ab
{
	int a;
	int b;
};

int n;
ab t[100];
std::string r[100];

ab cmp(ab i, ab j)
{
	return ab{std::max(i.a, j.a), std::min(i.b, j.b)};
}

ab add(ab i, ab j)
{
	return ab{i.a + j.a, i.b + j.b};
}

ab sub(ab i, ab j)
{
	return ab{ i.a - j.b, i.b - j.a };
}

int main()
{
	// Open Streams
	std::ifstream fin("traffic.in");

	std::ofstream fout("traffic.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read File
	fin >> n;

	for (int i = 0; i < n; i++)
	{
		int a;
		int b;
		fin >> r[i] >> a >> b;

		t[i] = {a, b};
	}

	// start from highest none and go down to mile 1
	int maxN;
	for (int i = n - 1; i >= 0; i--)
	{
		if (r[i] == "none")
		{
			maxN = i;
			break;
		}
	}

	ab cur = t[maxN];
	// go down the mile line
	for (int i = maxN - 1; i >= 0; i--)
	{
		// if next mile is none,
		if (r[i] == "none")
		{
			// compare
			cur = cmp(t[i], cur);
		}
		// off
		else if (r[i] == "off")
		{
			cur = add(t[i], cur);
		}
		// on
		else
		{
			cur = sub(cur, t[i]);
		}
	}

	if (cur.a < 0)
	{
		cur.a = 0;
	}
	if (cur.b < 0)
	{
		cur.b = 0;
	}

	fout << cur.a << " " << cur.b << "\n";

	// Go the other way
	// start at first "none" then go up to nth mile
	int minN;
	for (int i = 0; i < n; i++)
	{
		if (r[i] == "none")
		{
			minN = i;
			break;
		}
	}

	cur = t[minN];
	// go up
	for (int i = minN + 1; i < n; i++)
	{
		// if next one is "none"
		if (r[i] == "none")
		{
			cur = cmp(t[i], cur);
		}
		else if (r[i] == "on")
		{
			cur = add(t[i], cur);
		}
		else // (r[i] == "off")
		{
			cur = sub(cur, t[i]);
		}
	}
	if (cur.a < 0)
	{
		cur.a = 0;
	}
	if (cur.b < 0)
	{
		cur.b = 0;
	}
	fout << cur.a << " " << cur.b << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}