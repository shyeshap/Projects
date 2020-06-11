package il.co.ilrd.quizzes;

/*
 * Dynamic progranmming:
 * 1. Recursive solution
 * 2. Memorize intermediate results 
 */
// Returns the maximum value that can be put in a knapsack of capacity W 
public class KnapSack {

	/* A Naive recursive implementation of 0-1 Knapsack problem: 
	 *
	 * computes the same sub-problems again and again. 
	 * Time Complexity: O(2^n). As there are redundant subproblems.
	 * Auxiliary Space :No use of any data structure for storing values-: O(1)
	 *
	 */
	
	static int recursiveKnapSack(int W, int wt[], int val[], int n) { 
		// Base Case 
		if (n == 0 || W == 0)  
			return 0; 

		// If weight of the nth item is more than Knapsack capacity W, then 
		// this item cannot be included in the optimal solution 
		if (wt[n-1] > W) 
			return recursiveKnapSack(W, wt, val, n-1); 

		// Return the maximum of two cases:  
		// (1) nth item included  
		// (2) not included 
		else return Math.max(val[n - 1] + recursiveKnapSack(W - wt[n - 1], wt, val, n - 1), 
				recursiveKnapSack(W, wt, val, n - 1)); 
	} 
	
	/*
	 *  A Dynamic Programming based solution for 0-1 Knapsack problem:
	 *  
	 *  Time Complexity: O(N*W). where ‘N’ is the number of weight element and ‘W’ is capacity. 
	 *  As for every weight element we traverse through all weight capacities 1<=w<=W.
	 *  Auxiliary Space: O(N*W). 
	 *  The use of 2-D array of size ‘N*W’.
	 */

	static int dynamicKnapSack(int W, int wt[], int val[], int n) 
	{ 
		int i, w; 
		int K[][] = new int[n+1][W+1]; 

		// Build table K[][] in bottom up manner 
		for (i = 0; i <= n; i++) 
		{ 
			for (w = 0; w <= W; w++) 
			{
				System.out.println("i = " + i + " w = " + w);
				if (i == 0 || w == 0) {
					K[i][w] = 0; 
					System.out.println("i = 0 || w == 0 -> " + K[i][w]);
				}
				else if (wt[i - 1] <= w) { 
					K[i][w] = Math.max(val[i - 1] + K[i - 1][w - wt[i - 1]],  K[i - 1][w]);
					System.out.println("wt[i - 1] <= w -> max(" + val[i - 1] + "+" + K[i - 1][w - wt[i - 1]] 
							+ ", " + K[i - 1][w]);
				} else {
					K[i][w] = K[i - 1][w];
					System.out.println("wt[i - 1] > w -> K[i][w] = " + K[i - 1][w]);
				}
			} 
		} 

		return K[n][W]; 
	} 
	
	public static void main(String[] args) {
		int val[] = new int[]{60, 100, 120};
		int wt[] = new int[]{10, 20, 30};
		int W = 50;
		int n = val.length;
		System.out.println(recursiveKnapSack(W, wt, val, n));
		System.out.println(dynamicKnapSack(W, wt, val, n));

	}

}
