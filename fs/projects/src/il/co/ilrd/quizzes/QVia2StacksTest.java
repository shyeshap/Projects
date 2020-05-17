package il.co.ilrd.quizzes;
import java.util.Queue;
import java.util.concurrent.ArrayBlockingQueue;

import junit.framework.TestCase;

public class QVia2StacksTest extends TestCase {
	static Queue<Integer> q = new ArrayBlockingQueue<>(10);
	static QVia2Stacks myQ = new QVia2Stacks();
	
	public static void main(String[] args) {
		q.add(1);
		q.add(2);
		q.add(3);
		
		myQ.add(1);
		myQ.add(2);
		myQ.add(3);
		
		System.out.println(q.peek().equals(myQ.peek()));
		
		System.out.println("reg "+q.remove() +" my "+ myQ.remove());
		System.out.println("reg "+q.remove() +" my "+ myQ.remove());
		System.out.println("reg "+q.remove() +" my "+ myQ.remove());

	}
	
}
