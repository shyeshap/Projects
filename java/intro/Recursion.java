class Recursion
{
	public static void main(String[] args)
	{
		PrintNum(0);
	}

	public static void PrintNum(int num)
	{
		if (num == 10)
		{
			return;
		}

		System.out.println(num); 
		PrintNum(++num);
	}
}