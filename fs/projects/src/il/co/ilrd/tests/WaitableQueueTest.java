package il.co.ilrd.tests;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import il.co.ilrd.collection.WaitableQueue;
import java.util.concurrent.TimeUnit;

class WaitableQueueTest {
	WaitableQueue<String> q = new WaitableQueue<>();
	
	class RunnableDequeue implements Runnable {
		@Override
		public void run() {
			try {
				System.out.println("dequeue: " + q.dequeue());
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}				
		}
	}
	
	class RunnableEnqueue implements Runnable{

		@Override
		public void run() {
			q.enqueue(Thread.currentThread().getName());
		}
	}
		
	class RunnableDequeueWithTime implements Runnable {
		@Override
		public void run() {
			try {
				System.out.println("dequeue with time: " + q.dequeueWithTimeout(1, TimeUnit.SECONDS));
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}				
		}
	}	
	
	@Test
	void test() throws InterruptedException {
		Thread t = null;
		for (int i = 0; i < 10; ++i) {
			t = new Thread(new RunnableDequeueWithTime());
			t.start();
		}	
		
		for (int i = 0; i < 20; ++i) {
			t = new Thread(new RunnableDequeue());
			t.start();
		}
		for (int i = 0; i < 20; ++i) {
			t = new Thread(new RunnableEnqueue());
			t.start();
			
		}
		

		for (int i = 0; i < 10; ++i) {
			t = new Thread(new RunnableDequeueWithTime());
			t.start();
		}

		for (int i = 0; i < 20; ++i) {
			t = new Thread(new RunnableEnqueue());
			t.start();
		}
		
		for (int i = 0; i < 10; ++i) {
			t = new Thread(new RunnableDequeueWithTime());
			t.start();
		}	
		
		for (int i = 0; i < 100; ++i) {
			t.join();
		}
	}

}
