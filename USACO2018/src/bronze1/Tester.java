package bronze1;

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
    private static int first;
    private static int second;
    private static int third;

    private static int firstMax;
    private static int secondMax;
    private static int thirdMax;

    public static void main(String[] args)
    {
	BufferedReader in = null;
	try
	{
	    in = new BufferedReader(new FileReader("mixmilk.in"));
	} catch (FileNotFoundException e)
	{
	    e.printStackTrace();
	}

	try
	{
	    // first line
	    String line = in.readLine();
	    String[] vars = line.split(" ");

	    firstMax = Integer.parseInt(vars[0]);
	    first = Integer.parseInt(vars[1]);

	    // second line
	    line = in.readLine();
	    vars = line.split(" ");

	    secondMax = Integer.parseInt(vars[0]);
	    second = Integer.parseInt(vars[1]);

	    // third line
	    line = in.readLine();
	    vars = line.split(" ");

	    thirdMax = Integer.parseInt(vars[0]);
	    third = Integer.parseInt(vars[1]);
	} catch (IOException e)
	{
	    e.printStackTrace();
	}

	// CODE
	int bucketNum = 1;
	for (int i = 0; i < 100; i++)
	{
	    int start;
	    int end;
	    int startMax;
	    int endMax;

	    printValues();

	    if (bucketNum == 1)
	    {
		start = first;
		startMax = firstMax;

		end = second;
		endMax = secondMax;
	    } else if (bucketNum == 2)
	    {
		start = second;
		startMax = secondMax;

		end = third;
		endMax = thirdMax;
	    } else
	    {
		start = third;
		startMax = thirdMax;

		end = first;
		endMax = firstMax;
	    }

	    int[] out = pourMilk(start, startMax, end, endMax);

	    if (bucketNum == 1)
	    {
		first = out[0];

		second = out[1];
	    } else if (bucketNum == 2)
	    {
		second = out[0];

		third = out[1];
	    } else
	    {
		third = out[0];

		first = out[1];

	    }

	    bucketNum = addOne(bucketNum);
	}

	try
	{
	    in.close();
	} catch (IOException e)
	{
	    e.printStackTrace();
	}

	ArrayList<String> out = new ArrayList<String>();
	out.add("" + first);
	out.add("" + second);
	out.add("" + third);

	// write to out file
	try
	{

	    Files.write(Paths.get("mixmilk.out"), out, StandardCharsets.UTF_8, StandardOpenOption.CREATE);
	} catch (IOException e)
	{
	    System.err.println("x");
	    e.printStackTrace();
	}
    }

    public static int[] pourMilk(int start, int startMax, int end, int endMax)
    {
	int space = 0;

	space = endMax - end;

	if (space >= start)
	{
	    end += start;
	    start = 0;
	} else // if space < start
	{
	    start -= space;
	    end = endMax;
	}

	int[] out = new int[2];
	out[0] = start;
	out[1] = end;
	return out;
    }

    public static int addOne(int x)
    {
	x++;
	if (x > 3)
	{
	    x = 1;
	}

	return x;
    }

    private static void printValues()
    {
	System.out.println(first + ", " + second + ", " + third);
    }
}
