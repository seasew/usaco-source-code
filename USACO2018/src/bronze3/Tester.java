package bronze3;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.Set;
import java.util.StringTokenizer;

public class Tester
{
    private static int[] buckets1;
    private static int[] buckets2;
    private static Set<Integer> output;

    public static final int STARTING_GAL = 1000;
    public static final int NUM_OF_BUCKETS = 10;

    public static void main(String[] args)
    {
	try
	{
	    BufferedReader in = new BufferedReader(new FileReader("backforth.in"));

	    // Read File:
	    // get bucket values and store in arrays
	    // BUCKETS1
	    buckets1 = new int[NUM_OF_BUCKETS];
	    StringTokenizer t = new StringTokenizer(in.readLine());
	    for (int i = 0; i < NUM_OF_BUCKETS; i++)
	    {
		buckets1[i] = Integer.parseInt(t.nextToken());
	    }

	    // BUCKETS2
	    buckets2 = new int[NUM_OF_BUCKETS];
	    t = new StringTokenizer(in.readLine());

	    for (int i = 0; i < NUM_OF_BUCKETS; i++)
	    {
		buckets2[i] = Integer.parseInt(t.nextToken());
	    }

	    // Close Reader
	    in.close();

	    // initalize output storage
	    output = new HashSet<Integer>();

	    // iterate through two first buckets
	    for (int i1 = 0; i1 < buckets1.length; i1++)
	    {
		for (int i2 = i1 + 1; i2 < buckets1.length; i2++)
		{
		    // iterate through two second buckets
		    for (int j1 = 0; j1 < buckets2.length; j1++)
		    {
			for (int j2 = j1 + 1; j2 < buckets2.length; j2++)
			{
			    // subtract the two first buckets and add the two
			    // second buckets
			    output.add(STARTING_GAL - (buckets1[i1] + buckets1[i2]) + (buckets2[j1] + buckets2[j2]));
			}
		    }
		}

	    }

	    // case where you take the same bucket for two trips
	    for (int i = 0; i < buckets1.length; i++)
	    {
		for (int j = 0; j < buckets2.length; j++)
		{
		    // subtract the first bucket and add the second bucket
		    output.add(STARTING_GAL - buckets1[i] + buckets2[j]);
		}
	    }

	    output.add(STARTING_GAL);

	    // initialize out writer
	    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("backforth.out")));

	    out.println(output.size() + "");

	    out.close();

	} catch (IOException e)
	{
	    e.printStackTrace();
	}
    }
}
