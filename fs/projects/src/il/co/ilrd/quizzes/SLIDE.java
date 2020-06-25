
package il.co.ilrd.quizzes;

public class SLIDE {
	public static int sumKConsecutive(int[] arr, int k) {
		int startIndx = 0;

		if (k > arr.length) { return -1; }

		int sum =  sumSubArr(arr, k);
		int maxSum = sum;
		
		for (;k < arr.length; ++k, ++startIndx) {
			sum = sum - arr[startIndx] + arr[k];
			maxSum = Math.max(maxSum, sum);
		}
		
		return maxSum;
	}
	
	private static int sumSubArr(int[] arr, int end) {
		int sum = 0; 
		for (int i = 0; i < end; ++i) {
			sum += arr[i];
			
		}
		
		return sum;
	}
	
	public static void main(String[] args) {
		int[] arr = {100,200,300,400};
		System.out.println(sumKConsecutive(arr, 2));
		
		int[] arr1 = {1,4,2,10,23,3,1,0,20};
		System.out.println(sumKConsecutive(arr1, 4));
		
		int[] arr2 = {2,3};
		System.out.println(sumKConsecutive(arr2, 4));
		
		int[] arr3 = {1,2,3,4,5,6,7,8,9,-10,100};
		System.out.println(sumKConsecutive(arr3, 4));
	}
}