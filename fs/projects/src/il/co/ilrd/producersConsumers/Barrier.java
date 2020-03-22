package il.co.ilrd.producersConsumers;

import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.*;

public class Barrier {
	private final static int NumOfConsumers = 10;
	private static final Lock lock = new ReentrantLock();
	private static final Condition written = lock.newCondition();
	private static Semaphore sem = new Semaphore(0);
	private static int global;
	
	public class Producer implements Runnable {
		@Override
		public void run() {
			while (true) {
				for(int i = 0; i < NumOfConsumers; ++i) {
					try {
						sem.acquire();
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
								
				lock.lock();
				++global;
				write();
				written.signalAll();
				lock.unlock();
			}
		}
		
		private void write() {
				System.err.println(global);
			}	
		}
	
	
	public class Consumer implements Runnable {
		@Override
		public void run() {
			while (true) {
				int local = global;
				lock.lock();
				sem.release();
				while (global == local) {
					try {
						written.await();
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
				read();
				lock.unlock();
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			
		}
		
		private void read() {
			System.out.println(global);
		}
	}

	public static void main(String[] args) {
		Producer prod = new Barrier().new Producer();
		Consumer cons = new Barrier().new Consumer();
		
		new Thread(prod).start();
		
		for (int i = 0; i < NumOfConsumers; ++i) {
			new Thread(cons).start();
		}	
	}
}
