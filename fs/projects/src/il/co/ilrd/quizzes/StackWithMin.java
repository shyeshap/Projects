package il.co.ilrd.quizzes;
import java.util.Stack;

public class StackWithMin extends Stack<Integer> {
	
	Stack<Element> s;
	
	public StackWithMin() {
		s = new Stack<>();	
	}

	// implement the push , pop and min methods
	
	public Integer push(Integer num) {
		Integer min = s.peek().currMin;
		if (s.isEmpty() || num < min) {
			s.push(new Element(num, num));
		}
		
		else {
			s.push(new Element(num, min));
		}
		
		return num;
	}
	
	public Integer pop() {
		return s.pop().curr;
	}
	
	public Integer min() {
		return s.peek().currMin;
	}
	
	private class Element{
		Integer curr;
		Integer currMin;
		
		private Element (Integer curr, Integer currMin) {
			this.curr = curr;
			this.currMin = currMin;
		}
	}
}
