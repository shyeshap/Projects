package il.co.ilrd.concurrency;

public class ThreadCreate {
	
	public static class ThreadImpRunnable implements Runnable{
		@Override
		public void run() {
			System.out.println("thread implemnts runnable");
		}
	}
		
	public static class ThreadExtThread extends Thread {
		@Override
		public void run(){
			System.out.println("thread extends Thread");
		} 
	}
	
	public static void main(String[] args) {
		ThreadImpRunnable thr = new ThreadImpRunnable();
		Thread thread1 = new Thread(thr);
		thread1.start();
		
		ThreadExtThread thread2 = new ThreadExtThread();
		thread2.start();
	}

}

