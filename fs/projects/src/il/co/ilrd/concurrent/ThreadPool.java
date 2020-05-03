package il.co.ilrd.concurrent;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.Callable;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.FutureTask;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.RejectedExecutionException;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

import il.co.ilrd.collection.WaitableQueue;

public class ThreadPool {

	private int totalThreadsNum;
	private int pausedThreadsNum;
	private WaitableQueue<Task<?>> taskQueue = new WaitableQueue<>();
	private BlockingQueue<WorkerThread> endedThreads = new LinkedBlockingQueue<>();
	private volatile boolean poolRunning = true;
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
			new WorkerThread().start();
		}
	}

	private class WorkerThread extends Thread{
		private boolean threadRunning = true;

		@Override
		public void run() {
			while(threadRunning) {
				try {
					taskQueue.dequeue().future.run();
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
		private FutureTask<T> future;

		private Task(Callable<T> task, int priority) {
			this.priority = priority;
			this.future = new FutureTask<>(task);
		}

		@Override
		public int compareTo(Task<T> task) {
			return task.priority - this.priority;
		}
	}

	class killThreads implements Callable<WorkerThread>{

		@Override
		public WorkerThread call() {
			WorkerThread wt = (WorkerThread)Thread.currentThread();
			wt.disable();

			return wt;
		}
	}

	class ShutDown implements Runnable{

		@Override
		public void run() {
			WorkerThread wt = (new killThreads()).call();

			try {
				endedThreads.put(wt);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
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
			try {
				Task<T> t = new Task<>(task, priority.getPriorityVal());
				taskQueue.enqueue(t);

				return t.future;
			} catch(NullPointerException e) {
				throw new NullPointerException();			
			}
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
			initThreads(num - totalThreadsNum);
		} else {
			for (int i = 0; i < totalThreadsNum - num; ++i) {
				Task<WorkerThread> t = new Task<>(new killThreads(), Priority.HIGH.getPriorityVal() + 1);
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

		for (int i = 0; i < totalThreadsNum; ++i) {
			Task<Object> t = new Task<>(Executors.callable(new ShutDown()), Priority.LOW.getPriorityVal() - 1);
			taskQueue.enqueue(t);
		}
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
	public boolean awaitTermination(int timeOut, TimeUnit unit) throws InterruptedException {
		for (int i = 0; i < totalThreadsNum; ++i) {
			Thread t = endedThreads.poll(timeOut, unit);			
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
		class Pause implements Runnable{

			@Override
			public void run() {
				try {
					sem.acquire();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}	

		for (int i = 0; i < totalThreadsNum; ++i) {
			Task<Object> t = new Task<>(Executors.callable(new Pause()), Priority.HIGH.getPriorityVal() + 1);
			taskQueue.enqueue(t);
			pausedThreadsNum = totalThreadsNum;
		}
	}

	/**
	 * resuming after pause
	 */
	public void resume() {
		sem.release(pausedThreadsNum);
		pausedThreadsNum = 0;
	}
}