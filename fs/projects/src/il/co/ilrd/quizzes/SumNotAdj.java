package il.co.ilrd.quizzes;

public class SumNotAdj {
	/* Given a list of integers, write a function that returns the largest sum of non-adjacent numbers.
	 * Numbers can be 0 or negative.
	 * For example, [2, 4, 6, 2, 5] should return 13, since we pick 2, 6, and 5. [5, 1, 1, 5] 
	 * should return 10, since we pick 5 and 5.
	 */
	
	public int sumNotAdj(int[] nums) {
		int incl = nums[0];
		int excl = 0;
		int excl_new = 0;
		
		for (int i = 0; i < nums.length; ++i) {
			 /* current max excluding i */
			excl_new = incl > excl ? incl : excl;
			
			 /* current max including i */
			incl = excl + nums[i];
			excl = excl_new;
		}
		
		return ((incl > excl) ? incl : excl);
	}
	
	public static void main(String[] args) {
		
	}
}
