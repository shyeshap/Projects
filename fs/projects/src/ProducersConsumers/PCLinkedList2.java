package ProducersConsumers;

import java.util.LinkedList;
import java.util.concurrent.Semaphore;

public class PCLinkedList2 {
	static Semaphore sem = new Semaphore(0);
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
			sem.release();
			
					
		}
	}
	public class Consumer implements Runnable {
		@Override
		public void run() {
			try {
				sem.acquire();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
				synchronized (lock) {
					
					System.out.println("remove: " + list.remove());
				}
			}
			
		}
	
	public static void main(String[] args) {
		final int num_of_threads = 50;
		
		Producer prod = new PCLinkedList2().new Producer();
		Consumer cons = new PCLinkedList2().new Consumer();

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
