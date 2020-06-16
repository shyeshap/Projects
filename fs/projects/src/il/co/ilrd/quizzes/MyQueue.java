package il.co.ilrd.quizzes;

import java.util.Stack;

public class MyQueue {

	Stack<Integer> push;
	Stack<Integer> pop;

	public MyQueue() {
		push =new Stack<>();
		pop = new Stack<>();
	}

	public void push(Integer i) {
		push.push(i);
	}

	public Integer pop() {
		rearrange();
		return pop.pop();
	}

	private void rearrange() {
		if (pop.isEmpty()) {
			while (!push.isEmpty()) {
				pop.push(push.pop());
			}
		}
	}

	public Integer peek() {
		rearrange();
		return pop.peek();
	}

	public boolean isEmpty() {
		return (push.isEmpty() && pop.isEmpty());
	}

	public static void main(String[] args) {
		MyQueue q = new MyQueue();

		q.push(1);
		q.push(2);
		q.push(3);
		q.push(4);

		System.out.println(1 == q.peek());
		System.out.println(1 == q.pop());
		System.out.println(2 == q.pop());
		System.out.println(!q.isEmpty());
		System.out.println(3 == q.peek());
		q.push(5);
		System.out.println(3 == q.pop());
		System.out.println(4 == q.pop());
		System.out.println(5 == q.pop());
		System.out.println(q.isEmpty());

	}

}
