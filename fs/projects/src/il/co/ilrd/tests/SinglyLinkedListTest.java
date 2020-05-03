package il.co.ilrd.tests;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

import org.junit.jupiter.api.Test;

import il.co.ilrd.generic_singly_linked_list.EmptyListException;
import il.co.ilrd.generic_singly_linked_list.SinglyLinkedList;

class SinglyLinkedListTest {

	@Test
	void intTest() {
		SinglyLinkedList<Integer> intList = new SinglyLinkedList<>();
		assertTrue(intList.isEmpty());
		assertEquals(0, intList.size());
		
		intList.pushFront(1);
		assertFalse(intList.isEmpty());
		assertEquals(1, intList.size());
		assertEquals(1, intList.find(1).next());
		intList.pushFront(2);
		intList.pushFront(3);
		intList.pushFront(4);
		assertEquals(4, intList.size());
		SinglyLinkedList.print(intList);
		SinglyLinkedList<Integer> reversedIntList = SinglyLinkedList.newReverse(intList);
		SinglyLinkedList.print(reversedIntList);
		SinglyLinkedList<Integer> mergedIntList = SinglyLinkedList.Merge(intList, reversedIntList);
		SinglyLinkedList.print(mergedIntList);
		assertEquals(1, mergedIntList.find(1).next());
		assertEquals(2, mergedIntList.find(2).next());
		assertNull(mergedIntList.find(5).next());
		assertEquals(8, mergedIntList.size());
		try {
			mergedIntList.popFront();
		} catch (EmptyListException e) {
			e.printStackTrace();
		}			
	
		assertEquals(7, mergedIntList.size());
		SinglyLinkedList.print(mergedIntList);
	/*	try {
			emptyList.popFront();
		} catch (EmptyListException e) {
			e.printStackTrace();
		}
		*/
	}
	@Test
	void benTest() {
		SinglyLinkedList<Integer> sll1 = new SinglyLinkedList<>();
		SinglyLinkedList<Integer> sll2 = new SinglyLinkedList<>();
		SinglyLinkedList<Integer> sll3 = new SinglyLinkedList<>();
		
		sll1.pushFront(1); sll1.pushFront(2); sll1.pushFront(3); sll1.pushFront(4);
		sll2.pushFront(5); sll2.pushFront(6); sll2.pushFront(7); sll2.pushFront(8);	
	
		assertEquals(sll1.size(), 4);
		assertEquals(sll2.size(), 4);
		Iterator<Integer> iter = sll1.iterator();

		assertEquals(iter.next(), 4);
		assertEquals(iter.next(), 3);
		assertEquals(iter.next(), 2);
		assertEquals(iter.next(), 1);
		assertEquals(sll1.find(2).next(), 2);
		sll3 = SinglyLinkedList.Merge(sll1, sll2);
		Integer I = 8;
		/*for(Integer data: sll3) {
			assertEquals(I, data);
			--I;
		}*/
		SinglyLinkedList.print(sll3);
		while(!sll3.isEmpty()) {
			try {
				sll3.popFront();
			} catch (EmptyListException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		try {
			System.out.println(sll3.popFront());
		} catch (EmptyListException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Exception holder = new NullPointerException("ERROR: Can't Iter on empty list");
		}
		
		try {
			sll3.pushFront(47);
			Iterator<Integer> iter3 = sll3.iterator();
			sll3.pushFront(50);
			iter3.next();
		}catch (Exception e) {
			Exception holder2 = new ConcurrentModificationException("ERROR: Data Structre have been modified by another Iterator");
			System.out.println("the end.");
		}
	}

}
