package il.co.ilrd.quizzes;

public class Quiz_12_05 {
	static int findMaxSubArray(int arr[]) 
    { 
        int len = arr.length; 
        int maxTemp = 0; 
        int maxMax = arr[0];
        
        for (int i = 0; i < len; i++) 
        { 
            maxTemp = maxTemp + arr[i]; 
            System.out.println("temp = " + maxTemp);
            
            if (maxTemp < 0) {
            	maxTemp = 0; 
            	System.out.println("temp < 0 -> temp = 0");
            }
            
            else if (maxMax < maxTemp) {
                maxMax = maxTemp;
            	System.out.println("max < temp -> max = " + maxMax);
            }
            
        } 
        return maxMax; 
    } 
	
	public static void main(String[] args) {
		int[] arr = {-2, -1, 6, -4, 4, -2, 6, -5, -4};
		System.out.println("ans: " + findMaxSubArray(arr));
	}
}
