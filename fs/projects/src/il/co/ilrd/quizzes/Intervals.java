package il.co.ilrd.quizzes;

import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;

public class Intervals {
	public static int maxOverlapIntervalCount(int[] start, int[] end){
		int maxOverlap = 0;
		int tempOverlap = 0;
		
		if (start.length != end.length) { return -1; }
		
		PriorityQueue<Integer> q = new PriorityQueue<>(start.length + end.length, new Comparator<Integer>() {
		
			@Override
			public int compare(Integer i, Integer j) {
				return Math.abs(i) - Math.abs(j);
			}
			
		});
		
		for (int i = 0; i < start.length ; ++i ) {
			q.add(start[i]);
			q.add(end[i] * (-1));
		}
				
		for (int i = 0 ; i < q.size(); ++i) {
			if (q.remove() >= 0) { ++tempOverlap; }
			else { --tempOverlap; }
			
			if (tempOverlap > maxOverlap) { maxOverlap = tempOverlap; }
		}
		
		return maxOverlap;
		
	}
	
	public static int maxOverlapIntervalCountLut(int[] start, int[] end) {
		int[] lut = new int[24];
		Arrays.fill(lut, 0);
		int max = 0;
		
		if (start.length != end.length) { return -1; }
		
		for (int i = 0; i < start.length; ++i) {
			for (int j = start[i]; j <= end[i]; ++j) {
				++lut[j];
				max = max < lut[j] ? lut[j] : max;
			}
		}
		
		return max;
	}
	
	public static void main(String[] args) {
		int[] start = {0,3,4,7,1};
		int[] end = {2,7,6,8,5};
	
		System.out.println(maxOverlapIntervalCount(start, end));
		System.out.println(maxOverlapIntervalCountLut(start, end));
		
		int[] start1 = 	{0,9,2,1,15,7,11,7};
		int[] end1 = 	{20,10,3,10,18,13,16,10};
	
		System.out.println(maxOverlapIntervalCount(start1, end1));
		System.out.println(maxOverlapIntervalCountLut(start1, end1));
	}
	
}
