package il.co.ilrd.quizzes;
/*
 * QUIZ
* **Solve the 'Bursa' problem:**
* You are given an array, representing the prices of one stock over the course of a day.
* Each element in the array is the stock price at a specific time during the day, ordered by time, such that
* index 0 holds the first price of the stock for the day, and the last element is the last price.
* You want to find the prices where buying the stock, and then selling it, would make the biggest profit
* possible.
* Write a function that traverses the array exactly once, and returns the profit and the buy/sell indexes.
* 
* > Example: For the array of prices 6, 12, 3, 5, 1, 4, 9, 2 the buy index is 4, the sell index is 6,and the
* profit is 8.

---
You have 30 minutes.
Enjoy!
 */
public class Bursa {
	MaxProfit findMaxProf(int[] prices) {
		int tempBuy = 0, tempSell = 0, tempProfit = 0;
		MaxProfit max = new MaxProfit();
		
		for (int i = 0; i < prices.length; ++i) {
			tempProfit = prices[tempSell] - prices[tempBuy];
			
			if (tempProfit > max.maxProfit) {
				max.maxProfit = tempProfit;
				max.buyIndx = tempBuy;
				max.sellIndx = tempSell;
			
			}
			
			else if(tempProfit < 0) {
				tempBuy = tempSell;
			}
			
			++tempSell;
		}
		
		
		return max;
	}
	
	public class MaxProfit{
		private int buyIndx = 0, sellIndx = 0;
		private int maxProfit = 0;
	}
	
	public static void main(String[] args) {
		Bursa b = new Bursa();
		int[] bursa = {6, 12, 3, 5, 1, 4, 9, 2};
		
		MaxProfit max = b.findMaxProf(bursa);
		System.out.println("buy: " + max.buyIndx);
		System.out.println("sell: " + max.sellIndx);
		System.out.println("prof: " + max.maxProfit);
	}
}
