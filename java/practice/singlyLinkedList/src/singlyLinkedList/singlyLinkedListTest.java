package singlyLinkedList;

public class singlyLinkedListTest {

	public static void main(String[] args) {
		singlyLinkedList sll = new singlyLinkedList();
		System.out.println("size 0: " + (0 == sll.size()));
		System.out.println("is empty true: " + (true == sll.isEmpty()));
		sll.pushFront(1);
		System.out.println("size 1: " + (1 == sll.size()));
		System.out.println("is empty false: " + (false == sll.isEmpty()));
		sll.pushFront(2);
		System.out.println("size 2: " + (2 == sll.size()));
		System.out.println("poped 2: " + sll.popFront());
		System.out.println("size 1:	" + (1 == sll.size()));
		listIterator itr = sll.begin();
		System.out.println("next 1: " + itr.next()); 
		System.out.println("next null: " + itr.next()); 
		System.out.println("find 1: " + sll.find(1).next());
		System.out.println("find 2 (not exist): " + sll.find(2).next());
		sll.pushFront(3);
		sll.pushFront(4);
		System.out.println("find 3: " + sll.find(3).next());
		System.out.println("find 4: " + sll.find(4).next());
	}

}
