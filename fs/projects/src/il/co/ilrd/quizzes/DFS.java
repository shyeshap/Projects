package il.co.ilrd.quizzes;

import java.util.ArrayList;
import java.util.List;

import org.junit.Ignore;

public class DFS {
	public static int sumByDepth(List<Object> list) {
		int depth = 1;
		

		return helper(list, depth);
	
	}
	
	private static int helper(List<Object> list, int depth){
		int sum = 0;

		for (Object o : list) {
			if (o instanceof Integer) {
				sum += (Integer)o * depth;
			} else {
				sum += helper((List<Object>)o, ++depth);
			}
		}
		
		return sum;
	}

	public static void main(String[] args) {
		List<Object> list = new ArrayList<>();
		List<Object> innerList = new ArrayList<Object>();
		List<Object> innerInnerList = new ArrayList<Object>();
		list.add(1);
		list.add(innerList);
		innerList.add(4);
		innerList.add(innerInnerList);
		innerInnerList.add(6);
		list.add(2);
		System.out.println(list);
		
		System.out.println(sumByDepth(list));
	}
}
