package il.co.ilrd.multithreaded_counting_sort;

import java.util.Random;

public class Shuffle {
	public static void shuffleArray(char[] array) {
				
		Random rand = new Random();
		
		for (int i = 0; i < array.length; i++) {
			int randomIndexToSwap = rand.nextInt(array.length);
			char temp = array[randomIndexToSwap];
			array[randomIndexToSwap] = array[i];
			array[i] = temp;
		}
	}
}

