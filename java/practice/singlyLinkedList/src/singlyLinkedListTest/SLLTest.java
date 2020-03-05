package singlyLinkedListTest;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import singlyLinkedList.singlyLinkedList;

class SLLTest {
	
	@Test
	void sllTest() {
		//fail("Not yet implemented");
		singlyLinkedList sll = new singlyLinkedList();
		
		assertEquals(0, sll.size());
		assertTrue(sll.isEmpty());		
	}
	
	@Test
	void pushTest() {
		singlyLinkedList sll = new singlyLinkedList();
		
		sll.pushFront(1);
		assertFalse(sll.isEmpty());
		assertEquals(1, sll.size());
		sll.pushFront("hello");
		assertEquals(2, sll.size());
		sll.pushFront(2);
		assertEquals(3, sll.size());
		sll.pushFront(3);
		assertEquals(4, sll.size());
		sll.pushFront("shye");
		assertEquals(5, sll.size());
	}
	
	@Test
	void popTest() {
		singlyLinkedList sll = new singlyLinkedList();
		
		sll.pushFront(1);
		sll.pushFront(2);
		sll.pushFront("hi");
		sll.pushFront(3);
		sll.pushFront("shhhh");
		
		assertEquals(5, sll.size());
		assertEquals("shhhh", sll.popFront());
		assertEquals(4, sll.size());
		assertEquals(3, sll.popFront());
		assertEquals(3, sll.size());
		assertEquals("hi", sll.popFront());
		assertEquals(2, sll.size());
		assertEquals(2, sll.popFront());
		assertEquals(1, sll.size());
		assertEquals(1, sll.popFront());
		assertEquals(0, sll.size());
		assertEquals(null, sll.popFront());
	}
	
	@Test
	void findTest() {
		singlyLinkedList sll = new singlyLinkedList();
		
		sll.pushFront(1);
		sll.pushFront(2);
		sll.pushFront("hi");
		sll.pushFront(3);
		sll.pushFront("shhhh");
		
		assertEquals(1, sll.find(1).next());
		assertEquals("hi", sll.find("hi").next());
		assertEquals("shhhh", sll.find("shhhh").next());
		assertEquals(null, sll.find("shh").next());
	}

}
