package il.co.ilrd.collection;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Comparator;

import org.junit.jupiter.api.Test;

class PairTest {

	@Test
	void test() {
		Pair<Integer, Integer> pair = Pair.of(1, 2);
		assertEquals(1, pair.getKey());
		assertEquals(2, pair.getValue());
		System.out.println(pair.toString());
		
		Pair<Integer, Integer> swapped = Pair.swap(pair);
		assertEquals(2, swapped.getKey());
		assertEquals(1, swapped.getValue());
		System.out.println(swapped.toString());		
		
		assertFalse(pair.equals(swapped));
		assertTrue(pair.equals(Pair.of(1, 2)));
		
		Integer[] arrInt = {3,52,5,23,56,3,98};
		Pair<Integer, Integer> minMax = Pair.minMax(arrInt);
		assertEquals(3, minMax.getKey());
		assertEquals(98, minMax.getValue());
		
		class IntComparator implements Comparator<Integer> {

		    @Override
		    public int compare(Integer v1, Integer v2) {
		        return v1 < v2 ? -1 : v1 > v2 ? +1 : 0;
		    }
		}
		
		minMax = Pair.minMax(arrInt, new IntComparator());
		assertEquals(3, minMax.getKey());
		assertEquals(98, minMax.getValue());
		
		String[] arrStr = {"abc", "acb", "AAA", "dfg", "a"};
		Pair<String, String> minMaxStr = Pair.minMax(arrStr);
		assertEquals("AAA", minMaxStr.getKey());
		assertEquals("dfg", minMaxStr.getValue());
		
		Integer[] arrIntEven = {3,52, 1, 1000};
		minMax = Pair.minMax(arrIntEven, new IntComparator());
		assertEquals(1, minMax.getKey());
		assertEquals(1000, minMax.getValue());
		minMax = Pair.minMax(arrIntEven);
		assertEquals(1, minMax.getKey());
		assertEquals(1000, minMax.getValue());
		
		Integer[] arrIntOdd = {3,52, 1};
		minMax = Pair.minMax(arrIntOdd, new IntComparator());
		assertEquals(1, minMax.getKey());
		System.out.println();
		assertEquals(52, minMax.getValue());
		minMax = Pair.minMax(arrIntOdd);
		assertEquals(1, minMax.getKey());
		assertEquals(52, minMax.getValue());
		
	}

}
