package il.co.ilrd.concurrent;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.Callable;
import java.util.concurrent.CancellationException;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.RejectedExecutionException;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import il.co.ilrd.collection.WaitableQueue;

/**
 * non thread-safe ThreadPool
 * 
 * @author Shye Shapira
 *
 */
public class ThreadPool {

	private int totalThreadsNum;
	private int maxThreadsNum;
	private int pausedThreadsNum;
	private WaitableQueue<Task<?>> taskQueue = new WaitableQueue<>();
	private BlockingQueue<WorkerThread> endedThreads;
	private boolean poolRunning = true;
	private Semaphore sem = new Semaphore(0);

	public ThreadPool(int totalThreadsNum) {
		this.totalThreadsNum = totalThreadsNum;

		initThreads(totalThreadsNum);
	}

	/************************* IMP *****************************/
	public enum Priority {
		LOW	(1),
		MID	(5),
		HIGH(10);

		private int priorityVal;

		private Priority(int priorityVal) {
			this.priorityVal = priorityVal;
		}

		private int getPriorityVal(){
			return priorityVal;
		}
	}

	private void initThreads(int threadNum) {
		for (int i = 0; i < threadNum; ++i) {
			new WorkerThread(taskQueue).start();
		}
	}

	private static class WorkerThread extends Thread{
		private volatile boolean threadRunning = true;
		private WaitableQueue<Task<?>> taskQueue;
		
		WorkerThread(WaitableQueue<Task<?>> taskQueue){
			this.taskQueue = taskQueue;
		}
		
		@Override
		public void run() {
			while(threadRunning) {
				try {
					taskQueue.dequeue().execute();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}

		private void disable() {
			threadRunning = false;
		}
	}

	private static class Task<T> implements Comparable<Task<T>>{
		private int priority;
		private FutureTask future;
		private Callable<T> task;
		private boolean running = false;
		
		private Task(Callable<T> task, int priority) {
			this.priority = priority;
			this.task = task;
			this.future = new FutureTask();
		}
		
		private void execute() {
			if (!future.cancelled) {
				try {
					running = true;
					future.retVal = task.call();
				} catch (Exception e) {
					future.e = e;
				} finally {
					future.setResult();				
				}
			}
		}
		
		@Override
		public int compareTo(Task<T> task) {
			return task.priority - this.priority;
		}
		
		private class FutureTask implements Future<T>{
			private T retVal;
			private boolean cancelled = false;
			private boolean done = false;
			private CountDownLatch waitLatch = new CountDownLatch(1);
			private Exception e;
			
			private void setResult() {
				done = true;
				waitLatch.countDown();
			}
			
			/**
			 * Attempts to cancel execution of this task. This attempt will fail 
			 * if the task has already started, completed, has already been cancelled, 
			 * or could not be cancelled for some other reason. If successful, and 
			 * this task has not started when cancel is called, this task should never run.
			 * 
			 * After this method returns, subsequent calls to isDone() will always return 
			 * true. Subsequent calls to isCancelled() will always return true if this 
			 * method returned true.
			 * 
			 * @param arg - disabled
			 * @return false if the task could not be cancelled, typically because is 
			 * already executing; true otherwise 
			 */
			@Override
			public boolean cancel(boolean arg) {
				if (!running) {
					cancelled = true;
					done = true;					
				}
				
				return cancelled;
			}
			
			/**
			 * Waits if necessary for the computation to complete, and then retrieves its result.
			 * 
			 * @return the computed result
			 * @throws CancellationException - if the computation was cancelled
			 * @throws ExecutionException - if the computation threw an exception
			 * @throws InterruptedException - if the current thread was interrupted while waiting
			 */
			@Override
			public T get() throws InterruptedException, ExecutionException {
				if (isCancelled()) {
					throw new CancellationException();
				}
			//	e.fillInStackTrace();
				
				waitLatch.await();
				
				return retVal;
			}
			
			/**
			 * Waits if necessary for at most the given time for the computation to complete, 
			 * and then retrieves its result, if available.
			 *  
			 * @param timeout - the maximum time to wait
			 * @param unit - the time unit of the timeout argument
			 * @return the computed result
			 * @throws CancellationException - if the computation was cancelled
			 * @throws ExecutionException - if the computation threw an exception
			 * @throws InterruptedException - if the current thread was interrupted while waiting
			 */
			@Override
			public T get(long timeout, TimeUnit unit) 
					throws InterruptedException, ExecutionException, TimeoutException {
				if (isCancelled()) {
					throw new CancellationException();
				}
				                                                                                               
				if (!waitLatch.await(timeout, unit)) {
					throw new TimeoutException();
				}
				
				return retVal;
			}
			
			/**
			 * Returns true if this task was cancelled before it completed normally.
			 * 
			 * @return true if this task completed
			 */
			@Override
			public boolean isCancelled() { return cancelled; }
			
			/**
			 * Returns true if this task completed. Completion may be due to normal 
			 * termination, an exception, or cancellation -- in all of these cases, 
			 * this method will return true.
			 * 
			 * @return true if this task completed
			 */
			@Override
			public boolean isDone() { return done; }
			
		}
	}

	/**************************API*****************************/

	/**
	 * Submits a Runnable task for execution and returns a Future 
	 * representing that task. The Future's get method will return 
	 * null upon successful completion.
	 * 
	 * @param task - the task to submit
	 * @param priority
	 * @return a Future representing pending completion of the task
	 * @throws RejectedExecutionException - if the task cannot be scheduled for execution
	 * @throws NullPointerException - if the task is null
	 */
	public Future<Object> submit(Runnable task, Priority priority) {
		return submit(Executors.callable(task), priority);
	}

	/**
	 * Submits a Runnable task for execution and returns a Future 
	 * representing that task. The Future's get method will return 
	 * the given result upon successful completion.
	 * 
	 * @param task -  the task to submit
	 * @param priority - priority of task
	 * @param result - the result to return
	 * @return a Future representing pending completion of the task
	 * @throws RejectedExecutionException - if the task cannot be scheduled for execution
	 * @throws NullPointerException - if the task is null
	 */
	public <T> Future<T> submit(Runnable task, Priority priority, T result) {
		return submit(Executors.callable(task, result), priority);
	}

	/**
	 * * Submits a Runnable task for execution and returns a Future 
	 * representing that task. The Future's get method will return 
	 * the given result upon successful completion.
	 * 
	 * @param task -  the task to submit
	 * @throws RejectedExecutionException - if the task cannot be scheduled for execution
	 * @throws NullPointerException - if the task is null
	 */
	public <T> Future<T> submit(Callable<T> task) {
		return submit(task, Priority.MID);
	}

	/**
	 * Submits a Runnable task for execution and returns a Future 
	 * representing that task. The Future's get method will return 
	 * the given result upon successful completion.
	 * 
	 * @param task -  the task to submit
	 * @param priority - priority of task
	 * @return a Future representing pending completion of the task
	 * @throws RejectedExecutionException - if the task cannot be scheduled for execution
	 * @throws NullPointerException - if the task is null
	 */
	public <T> Future<T> submit(Callable<T> task, Priority priority) {
		if (poolRunning) {
			Task<T> t = new Task<>(task, priority.getPriorityVal());
			taskQueue.enqueue(t);
			return t.future;
		}
		throw new RejectedExecutionException();
	}

	/** 
	 * Adjust number of threads in pool.
	 * 
	 * @param num - new number of threads in pool
	 */
	public void setNumOfThreads(int num) {
		if (totalThreadsNum < num) {
			if (maxThreadsNum < num) { maxThreadsNum = num; }
			initThreads(num - totalThreadsNum);
		} else {
			Task<Object> t = new Task<>(Executors.callable(() -> {
				WorkerThread wt = (WorkerThread)Thread.currentThread();
				wt.disable();
				endedThreads.add(wt);
			}), Priority.HIGH.getPriorityVal() + 1);
			
			for (int i = 0; i < totalThreadsNum - num; ++i) {
				taskQueue.enqueue(t);
			}
		}

		totalThreadsNum = num;
	}
	
	/**
	 * Initiates an orderly shutdown in which previously submitted tasks are executed, 
	 * but no new tasks will be accepted. Invocation has no additional effect if 
	 * already shut down.
	 * 
	 * This method does not wait for previously submitted tasks to complete execution. 
	 * Use awaitTermination to do that.
	 * 
	 * @throws SecurityException - if a security manager exists and shutting down 
	 * this ExecutorService may manipulate threads that the caller is not permitted 
	 * to modify because it does not hold RuntimePermission("modifyThread"), or the 
	 * security manager's checkAccess method denies access.
	 */

	public void shutdown() {	
		poolRunning = false;
		endedThreads = new LinkedBlockingQueue<>();

		setNumOfThreads(0);
	}

	/**
	 * Blocks until all tasks have completed execution after a shutdown request, 
	 * or the timeout occurs, or the current thread is interrupted, 
	 * whichever happens first.
	 * 
	 * @param timeOut - the maximum time to wait
	 * @param unit - the time unit of the timeout argument
	 * @return true if this executor terminated and false if the timeout elapsed before termination
	 * @throws InterruptedException - if interrupted while waiting
	 */
	public boolean awaitTermination(long timeout, TimeUnit unit) throws InterruptedException {
		long endTime = System.currentTimeMillis() + TimeUnit.MILLISECONDS.convert(timeout, unit);
		
		for (int i = 0; i < totalThreadsNum; ++i) {
			Thread t = endedThreads.poll(endTime - System.currentTimeMillis(), TimeUnit.MILLISECONDS);			
			if (t == null) { return false; }

			t.join();
		}

		return true;
	}

	/**
	 * 
	 * pauses thread-pool run after returning from current executed tasks. 
	 * call resume() to continue
	 *   
	 */
	public void pause() {	
		Task<Object> t = new Task<>(Executors.callable(() -> {
			try {
				sem.acquire();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}), Priority.HIGH.getPriorityVal() + 1);

		for (int i = 0; i < totalThreadsNum; ++i) {
			taskQueue.enqueue(t);
		}
		pausedThreadsNum = totalThreadsNum;
	}

	/**
	 * resuming after pause
	 */
	public void resume() {
		sem.release(pausedThreadsNum);
		pausedThreadsNum = 0;
	}
}