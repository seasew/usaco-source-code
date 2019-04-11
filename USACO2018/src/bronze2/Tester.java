package bronze2;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;

public class Tester
{

    private static ArrayList<Boolean> buckets;
    private static int[][] values;
    private static int n;

    public static void main(String[] args)
    {
	BufferedReader in = null;
	try
	{
	    in = new BufferedReader(new FileReader("blist.in"));
	} catch (FileNotFoundException e)
	{
	    e.printStackTrace();
	}

	buckets = new ArrayList<Boolean>();

	// Read the in file
	try
	{
	    String nStr = in.readLine();
	    n = Integer.parseInt(nStr);

	    values = new int[n][3];

	    for (int i = 0; i < n; i++)
	    {
		String line = in.readLine();
		String[] valuesStr = line.split(" ");

		values[i][0] = Integer.parseInt(valuesStr[0]);
		values[i][1] = Integer.parseInt(valuesStr[1]);
		values[i][2] = Integer.parseInt(valuesStr[2]);
	    }
	} catch (IOException e)
	{
	    e.printStackTrace();
	}

	// close file reader
	try
	{
	    in.close();
	} catch (IOException e)
	{
	    e.printStackTrace();
	}

	// Calculate:
	for (int t = 1; t <= 1000; t++)
	{
	    int startingBuckets = checkList(0, t);
	    invert(startingBuckets, true);

	    int endingBuckets = checkList(1, t);
	    invert(endingBuckets, false);

	}

	// write to file
	ArrayList<String> out = new ArrayList<String>();
	out.add("" + buckets.size());
	try
	{

	    Files.write(Paths.get("blist.out"), out, StandardCharsets.UTF_8, StandardOpenOption.CREATE);
	} catch (IOException e)
	{
	    e.printStackTrace();
	}
    }

    private static int checkList(int index, int value)
    {
	int out = 0;
	for (int i = 0; i < n; i++)
	{
	    if (values[i][index] == value)
	    {
		out += values[i][2];
	    }
	}

	return out;
    }

    private static int[] ArrayListToArray(ArrayList<Integer> list)
    {
	int[] out = new int[list.size()];
	for (int i = 0; i < list.size(); i++)
	{
	    out[i] = list.get(i);
	}

	return out;
    }

    private static void invert(int num, boolean value)
    {
	if (num > 0)
	{
	    // check each bucket
	    for (int i = 0; i < buckets.size(); i++)
	    {
		if (num > 0)
		{
		    // find opposite buckets
		    if (buckets.get(i) != value)
		    {
			// change to value
			buckets.set(i, value);
			num--;
		    }
		} else
		{
		    break;
		}
	    }
	}

	for (int i = num; i > 0; i--)
	{
	    buckets.add(value);
	}
    }

}
