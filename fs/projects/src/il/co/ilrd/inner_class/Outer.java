package il.co.ilrd.inner_class;

public class Outer {
	
	int a = 2;
	
	public int foo() {
		return 1;
	}
	
	public class Inner {
		int x = foo();
		
		public void foo2() {
			System.out.println(x);
			
			x = a;
			
			System.out.println(x);
		}
	}
	
	public void main(String[] vars) {
		Outer outer = new Outer();
		Outer.Inner inner = outer.new Inner();
	}
}