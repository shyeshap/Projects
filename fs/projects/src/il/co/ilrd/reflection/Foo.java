package il.co.ilrd.reflection;

public class Foo {
	public int i = 1;
	private String s = "Hello";
	
	public Foo() {System.out.println("constructor");};
	
	public void f1() {
		System.out.println(s);
	}
}
