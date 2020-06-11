package il.co.ilrd.quizzes;

import java.util.Arrays;

public class Multiply {
	public static int[] mult(int[] numbers) {
		int[] ans = new int[numbers.length];
		int mult = 1;
		
		for (int i : numbers) {
			mult *= i; 
			System.out.println(mult);
		}
		
		for (int i = 0; i < numbers.length; ++i) {
			ans[i] = mult / numbers[i];
		}
		
		return ans;
	}
	
	public static void main(String[] args) {
		int[] num = {1,2,3,4,5};
		System.out.println(Arrays.toString(mult(num)));
	}
}
