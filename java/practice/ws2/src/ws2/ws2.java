class baseClass {
	static int v1;
	
	static {
		v1 = 10;
	}
}

class derivedClass extends baseClass {
	static String str;
	
	static {
		str = "hello"
	}
}

public class ws2 {
	public static void main(String[] args) {
		useful[] x = { 
				new useful(),
				new moreUsful()
		};
		
		x[0].f();
		x[1].g();
		//x[1].i();
	}
}