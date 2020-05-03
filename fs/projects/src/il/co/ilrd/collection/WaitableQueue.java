/**  
 * 
 * @author Shye Shapira
 *
 */
package il.co.ilrd.collection;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

public class WaitableQueue<E> {
	private Object mutex = new Object();
	private final Semaphore sem = new Semaphore(0);
	private Queue<E> queue;
	
	/**
     * Creates a {@code WaitableQeue} with the default
     * initial capacity (11) that orders its elements according to
     * their {@linkplain Comparable natural ordering}.
     */
	public WaitableQueue() {
		queue = new PriorityQueue<>();
	}
	
	/**
     * Creates a {@code WaitableQeue} with the default
     * initial capacity (11) that orders its elements according 
     * to the specified comparator.
     *
     * @param  comparator the comparator that will be used to order this
     *         priority queue.  If {@code null}, the {@linkplain Comparable
     *         natural ordering} of the elements will be used.
     */
	public WaitableQueue(Comparator<E> comparator) {
		queue = new PriorityQueue<>(comparator);
	}
	
	/**
     * Inserts the specified element into this priority queue.
     * As the queue is unbounded, this method will never block.
     *
     * @param e the element to add
     * @throws ClassCastException if the specified element cannot be compared
     *         with elements currently in the priority queue according to the
     *         priority queue's ordering
     * @throws NullPointerException if the specified element is null
     */
	public void enqueue(E e) {
		synchronized(mutex){
			try {
				queue.add(e);
			} catch(NullPointerException ex) {
				throw new NullPointerException("enqueued null element");
			} catch (ClassCastException ex) {
				throw new ClassCastException("enqueued element is incompetible type");
			}
			sem.release();
		}
	}
	
	/**
	 * blocking if the queue is empty, will return E element 
	 * @return
	 * @throws InterruptedException 
	 */
	public E dequeue() throws InterruptedException {
		sem.acquire();
		synchronized(mutex){
			return queue.poll();
			
		}
	}
	
	//blocking if the queue is empty for maximum of timeout TimeUnit,
	//will return E element or null timeout 
	public E dequeueWithTimeout(long timeout, TimeUnit unit) throws InterruptedException{
		if(sem.tryAcquire(timeout, unit)) {
			synchronized(mutex){
				return queue.poll();
			}
		}else {
			return null;
		}
	}
}

