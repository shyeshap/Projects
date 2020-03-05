package singlyLinkedList;

public class singlyLinkedListTest {

	public static void main(String[] args) {
		singlyLinkedList sll = new singlyLinkedList();
		System.out.println("size 0: " + (0 == sll.size()));
		System.out.println("is empty true: " + (true == sll.isEmpty()));
		sll.pushFront(1);
		System.out.println("size 1: " + (1L == sll.size()));
		System.out.println("is empty false: " + (false == sll.isEmpty()));
		sll.pushFront(2);
		System.out.println("size 2: " + (2 == sll.size()));
		System.out.println("poped 2: " + sll.popFront());
		System.out.println("size 1:	" + (1 == sll.size()));
		listIterator itr = sll.begin();
		System.out.println(itr.next()); // 1
		System.out.println(itr.next()); // null
		System.out.println("find 1: " + sll.find(1).next());
		System.out.println("find 2: " + sll.find(2).next());
	}

}
