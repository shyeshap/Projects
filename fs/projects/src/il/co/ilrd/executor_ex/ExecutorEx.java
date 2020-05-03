package il.co.ilrd.executor_ex;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

public class ExecutorEx {


	public static void main(String[] args) throws ExecutionException, InterruptedException {
		ExecutorService single = Executors.newSingleThreadExecutor();
		ExecutorService fixed = Executors.newFixedThreadPool(3);
		ExecutorService cached = Executors.newCachedThreadPool();
		ExecutorService schduled = Executors.newScheduledThreadPool(3);

		Future<String> future = single.submit(() -> {
			try {
				for (int i = 0; i < 100; i++) {
					System.out.println("single");
					Thread.sleep(10);
				}
				System.out.println("single Asynchronous Callable");
			} catch (InterruptedException e) {
				System.out.println("interuppted");
			}
			return "single done";
		});

		Future<String> future1 = fixed.submit(() -> {
			try {
				for (int i = 0; i < 100; i++) {
					System.out.println("fixed");
					Thread.sleep(10);
				}
				System.out.println("fixed Asynchronous Callable");
			} catch (InterruptedException e) {
				System.out.println("interuppted");
			}

			return "fixed done";
		});

		Future<String> future2 = cached.submit(() -> {
			try {
				for (int i = 0; i < 100; i++) {
					System.out.println("cached");
					Thread.sleep(10);
				}
				System.out.println("cached Asynchronous Callable");
			} catch (InterruptedException e) {
				System.out.println("interuppted");
			}

			return "cached done";
		});


		Future<String> future3 = schduled.submit(() -> {
			try {
				for (int i = 0; i < 100; i++) {
					System.out.println("schduled");
					Thread.sleep(10);
				}
				System.out.println("Asynchronous Callable");
			} catch (InterruptedException e) {
				System.out.println("interuppted");
			}

			return "schduled done";
		});

		try {
			System.err.println(future.get());
			System.err.println(future1.get());
			System.err.println(future2.get());
			System.err.println(future3.get());
		} catch (InterruptedException | ExecutionException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		single.shutdown();
		single.awaitTermination(10, TimeUnit.SECONDS);
		fixed.shutdown();
		fixed.awaitTermination(10, TimeUnit.SECONDS);
		cached.shutdown();
		cached.awaitTermination(10, TimeUnit.SECONDS);
		schduled.shutdown();
		schduled.awaitTermination(10, TimeUnit.SECONDS);

	}

}
