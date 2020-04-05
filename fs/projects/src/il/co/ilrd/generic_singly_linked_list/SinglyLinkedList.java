package il.co.ilrd.generic_singly_linked_list;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

public class SinglyLinkedList<T> implements Iterable<T> {
	private Node<T> head = new Node<>(null, null);
	private volatile int listModCount = 0;
		
	private static class Node<T> {
		private T data;
		private Node<T> nextNode;
		
		private Node(T data, Node<T> nextNode) {
			this.data = data;
			this.nextNode = nextNode;
		}
	}
	
	private static class ListIteratorImp<T> implements Iterator<T> {
		private Node<T> curr;
		private volatile int modCount;
		private SinglyLinkedList<T> list;
		
		private ListIteratorImp(SinglyLinkedList<T> list) {
			curr = list.head;
			this.list = list;
			modCount = list.listModCount;
		}
		
		@Override
		public boolean hasNext() {
			return curr.nextNode != null;
		}
		
		@Override
		public T next() {
			T data = curr.data;
					
			if (modCount != list.listModCount)
			{
				throw new ConcurrentModificationException();
			}
			
			if (this.hasNext()) {
				curr = curr.nextNode;
			}
			
			return data;
		}
	}
	
	@Override
	public Iterator<T> iterator() {
		return new ListIteratorImp<T>(this);
	}
	
	public void pushFront(T data) {
		Node<T> newNode = new Node<>(data, head);
		head = newNode;
		++listModCount;
	}
	
	public T popFront() throws EmptyListException {
		if (this.isEmpty()) {
			throw new EmptyListException("Cant pop from empty list");
		}
		
		T data = head.data;
		head = head.nextNode;
		++listModCount;
		
		return data;
	}
	
	public int size() {
		int size = 0;
		
		for (T type : this) {
			++size;
		}
		
		return size;
	}
	
	public Iterator<T> find(T data) {
		ListIteratorImp<T> itr = new ListIteratorImp<>(this);
		
		while (itr.hasNext() && !(data.equals(itr.curr.data))) {
			itr.next();
		}
		
		return itr;
	}
	
	public boolean isEmpty() {
		return head.nextNode == null;
	}
	
	public static <E> SinglyLinkedList<E> Merge(SinglyLinkedList<E> list1, SinglyLinkedList<E> list2) {
		if (list1 == null || list2 == null) {
			throw new NullPointerException();
		}
		
		SinglyLinkedList<E> merged = new SinglyLinkedList<>();
		
		for (E element : list1) {
			merged.pushFront(element);
		}
		
		for (E element : list2) {
			merged.pushFront(element);
		}

		return newReverse(merged);
	}
	
	public static <E> SinglyLinkedList<E> newReverse(SinglyLinkedList<E> list) {
		if (list == null) {
			throw new NullPointerException();
		}
		
		SinglyLinkedList<E> reversed = new SinglyLinkedList<E>();
		
		for (E element : list) {
			reversed.pushFront(element);
		}
		
		return reversed;
	}
	
	public static <E> void print(SinglyLinkedList<E> list) {
		if (list == null) {
			throw new NullPointerException();
		}
		
		for (E element : list) {
			System.out.print(element.toString());
		}

		System.out.println();
	}
	
}
