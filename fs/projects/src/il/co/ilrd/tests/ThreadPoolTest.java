package il.co.ilrd.tests;

import static org.junit.jupiter.api.Assertions.*;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

import org.junit.jupiter.api.Test;

import il.co.ilrd.concurrent.ThreadPool;
import il.co.ilrd.concurrent.ThreadPool.Priority;

class ThreadPoolTest{

	@Test
	void testSubmit() {
		ThreadPool t = new ThreadPool(3);
		Future<?> f = t.submit(new Runnable() {
			@Override
			public void run() {
				System.out.println("MID!!!!");	
			}	
		}, Priority.MID);

		Future<String> f1 = t.submit(new Runnable() {
			@Override
			public void run() {
				System.out.println("LOW!!!!");	
			}	
		}, Priority.LOW, "Run");

		try {
			assertEquals("Run", f1.get());
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (ExecutionException e) {
			e.printStackTrace();
		}

		Future<String> f2 = t.submit(() -> {
			System.out.println("MID call");
			return "call";
		});

		try {
			assertEquals("call", f2.get());
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (ExecutionException e) {
			e.printStackTrace();
		}

		Future<String> f3 = t.submit(new Callable<String>() {
			@Override
			public String call() {

				System.out.println("HIGH callable 2");
				return "call2";
			}
		}, Priority.HIGH);

		try {
			assertEquals("call2", f3.get());
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (ExecutionException e) {
			e.printStackTrace();
		}

		t.shutdown();
		try {
			assertTrue(t.awaitTermination(30, TimeUnit.SECONDS));
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		t.setNumOfThreads(10);
	}

	@Test
	void testPaus(){
		class Calling implements Callable<String>{

			@Override
			public String call() throws Exception {
				for (int i = 0; i < 20; ++i) {
					System.out.println(Thread.currentThread().getName());
					Thread.sleep(100);
				}
				return "Done!";
			}

		}

		ThreadPool t = new ThreadPool(3);
		for (int i = 0; i < 2; ++i) {
			Future<String> f = t.submit(new Calling());
			try {
				assertEquals("Done!", f.get());
			} catch (InterruptedException | ExecutionException e) {
				e.printStackTrace();
			}
			t.pause();
			try {
				System.out.println("paused");
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			t.resume();
		}

		t.shutdown();
		try {
			assertTrue(t.awaitTermination(30, TimeUnit.SECONDS));
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

	}

	@Test
	void priorityTest() {
		ThreadPool t = new ThreadPool(3);
		for (int i = 0; i < 30; ++i) {
			t.submit(() -> {
				System.out.println("LOW");
				Thread.sleep(100);
				return "low";
			}, Priority.LOW);

			t.submit(() -> {
				System.out.println("MID");
				Thread.sleep(100);
				return "mid";
			}, Priority.MID);

			t.submit(() -> {
				System.out.println("HIGH");
				Thread.sleep(100);
				return "high";
			}, Priority.HIGH);
		}

		t.shutdown();
		try {
			assertTrue(t.awaitTermination(30, TimeUnit.SECONDS));
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		t.shutdown();
	}

	@Test
	void pauseSetResume() throws InterruptedException {
		ThreadPool pool = new ThreadPool(10);
		pool.pause();
		pool.setNumOfThreads(5);
		pool.resume();
		Callable<String> callable = ()->{
			System.err.println("this is callable " + Thread.currentThread());
			assertEquals(1, 1);
			return "end";
		};
		pool.submit(callable);
		pool.shutdown();
		try {
			assertTrue(pool.awaitTermination(10, TimeUnit.SECONDS));
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("finish");

	}
}


