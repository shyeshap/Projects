package il.co.ilrd.producersConsumers;

import java.util.LinkedList;

public class PCLinkedList1 {
	
	static LinkedList<Integer> list = new LinkedList<Integer>();
	Object lock = new Object();
	Integer number = 0;
	
	public class Producer implements Runnable {
		@Override
		public void run() {
			synchronized (lock) {
				list.add(++number);
				System.out.println("add " + list.peekLast());
			}
					
		}
	}
	public class Consumer implements Runnable {
		@Override
		public void run() {
				while (list.isEmpty());
				synchronized (lock) {
					System.out.println("remove: " + list.remove());
				}
			}
			
		}
	
	public static void main(String[] args) {
		final int num_of_threads = 80;
		
		Producer prod = new PCLinkedList1().new Producer();
		Consumer cons = new PCLinkedList1().new Consumer();

		for (int i = 0; i < num_of_threads; ++i) {
			new Thread(prod).start();
			new Thread(cons).start();
			
		}
		
		try {
			Thread.sleep(10000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
	}

}