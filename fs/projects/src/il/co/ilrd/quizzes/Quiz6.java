package il.co.ilrd.quizzes;

public class Quiz6	{
	interface Person{
		default void sayHello() {
			System.out.println("Hello person");
		}
	}

	interface Male extends Person{
		default void sayHello() {
			System.out.println("hi male");
		}
	}

	static class Sam implements Person, Male {
		
	}

	public static void main(String[] args) {
		Sam sam = new Sam();
		sam.sayHello();
	}
}

