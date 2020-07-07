package il.co.ilrd.quizzes;

import java.util.PriorityQueue;

public class StackByHeap {
	PriorityQueue<stackHeapElement> heap = new PriorityQueue<>();
	
	void push(int num) {
		heap.add(new stackHeapElement(num));
	}

	int pop() {
		return heap.poll().num;
	}

	private static class stackHeapElement implements Comparable<stackHeapElement> {
		private static int count;
		private int counter;
		private int num;
		
		stackHeapElement(int num) {
			counter = ++count;
			this.num = num;
		}

		@Override
		public int compareTo(stackHeapElement obj) {
			return obj.getCounter() - this.counter;
		}
		
		public int getCounter() {
			return counter;
		}
	}


	public static void main(String[] args) {
		StackByHeap s = new StackByHeap();
		
		s.push(9);
		s.push(2);
		s.push(6);
		s.push(1);
		s.push(5);
		
		System.out.println("1: " + s.pop());
		System.out.println("2: " + s.pop());
		System.out.println("3: " + s.pop());
		System.out.println("4: " + s.pop());
		System.out.println("5: " + s.pop());
	}

}
