package il.co.ilrd.exceptions;

import java.io.IOException;

public class Foo {
	
	static byte[] ex = new byte[100];
	
	public class MyException1 extends RuntimeException{

		public MyException1(String string) {
			// TODO Auto-generated constructor stub
		}
		
	}
	
	public class MyException2 extends IOException {

		public MyException2(String string) {
			// TODO Auto-generated constructor stub
		}
		
	}

	public static void func1() throws IOException {
		System.out.println("func1: checked exception");
		
		throw new IOException("IO exception thrown from func1");		
	}
	
	public static void func2() {
		System.out.println("func2: Unchecked exception");

		throw new NullPointerException("Null pointer exception thrown from func2");
	}

	public static void func3() {
		System.out.println("func3: my Unchecked runtime exception");
		
		throw new Foo().new MyException1("myException1 thrown from func3");
	}
	
	public static void func4() throws IOException {
		System.out.println("func4: My checked exception");
		
		throw new Foo().new MyException2("myException2 thrown from func4");
	}
	
	
	public static void main(String[] args) {
		try {
			Foo.func1();
		} catch (IOException e) {
			
			e.printStackTrace();
		}
		
		Foo.func2();
		
		Foo.func3();
		
		try {
			Foo.func4();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		ex[101] = 3;

	}

}
