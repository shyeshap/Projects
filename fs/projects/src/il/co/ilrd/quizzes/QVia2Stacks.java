package il.co.ilrd.quizzes;
import java.util.Stack;

public class QVia2Stacks {
	Stack<Integer> s1, s2;

	public QVia2Stacks() {
		s1 = new Stack<>();
		s2 = new Stack<>();
	}

	// implement the size , peek and remove methods
	
	public void add(Integer num) {
		s1.add(num);
	}
	
	public int size() {
		return s1.size() + s2.size();
	}
	
	public int peek() {
		if (s2.isEmpty()) {
			while (!s1.isEmpty()) {
				s2.add(s1.pop());
			}
		}
		
		return s2.peek();
	}
	
	public int remove() {
		if (s2.isEmpty()) {
			while (!s1.isEmpty()) {
				s2.add(s2.pop());
			}
		}
		
		return s2.pop();
	}
}
