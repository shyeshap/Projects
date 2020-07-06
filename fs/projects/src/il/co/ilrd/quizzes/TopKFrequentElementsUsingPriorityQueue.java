package il.co.ilrd.quizzes;

import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Map.Entry;
import java.util.PriorityQueue;
import java.util.Set;

public class TopKFrequentElementsUsingPriorityQueue {

	/*
	 * Given a non-empty array of integers, return the k most frequent elements.
	 * 
	 * Input: nums = [1,1,1,2,2,3], k = 2
	 * Output: [1,2]
	 * 
	 */
	public int[] topKFrequent(int[] nums, int k) {
		int[] ret = new int[k];
		Map<Integer, Integer> map = new HashMap<>();
		Set<FrequentElement> set = new HashSet<>();
		PriorityQueue<FrequentElement> pq = new PriorityQueue<>();
		
		for (int i = 0; i < nums.length; ++i) {
			if (map.containsKey(nums[i])) {
				map.put(nums[i], map.get(nums[i]) + 1);				
			} else {
				map.put(nums[i], 1);	
			}
		}
		
		for (Entry<Integer, Integer> e : map.entrySet()) {
			pq.add(new FrequentElement(e.getKey(), e.getValue()));
		}
		
		for (int i = 0; i < k; ++i) {
			FrequentElement fe = pq.remove();
			ret[i] = fe.num;
		}
		return ret;
	}
	
	private class FrequentElement implements Comparable{
		int frequency;
		int num;
		
		public FrequentElement(int frequency, int num) {
			super();
			this.frequency = frequency;
			this.num = num;
		}
		
		@Override
		public int compareTo(Object fe) {
			if (!(fe instanceof FrequentElement)) {
				throw new ClassCastException();
			}
			
			return (((FrequentElement)fe).frequency - this.frequency);
		}
	}


	public static void main(String[] args) {
		TopKFrequentElementsUsingPriorityQueue tfe = new TopKFrequentElementsUsingPriorityQueue();
		int[] nums = {1,1,1,2,2,3};
		int k = 2;
		
		System.out.println(Arrays.toString(tfe.topKFrequent(nums, k)));
	}
}
