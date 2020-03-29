package il.co.ilrd.reflection;

import java.lang.reflect.*;

public class ObjectAnalizer {

	public static void main(String[] args) throws InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException {
		Foo f = new Foo();
		Class cls = f.getClass();
		Class supeCls = cls.getSuperclass();
		Constructor[] constructors = cls.getConstructors();
		Class[] interfaces = cls.getInterfaces();
		Field[] fields = cls.getDeclaredFields();
		Method[] methods = cls.getDeclaredMethods();
		Foo fo = (Foo) constructors[0].newInstance();
		fo.f1();
		
		System.out.println("name: " + cls.getName());
		System.out.println("super: " + supeCls.getName());
		
		for (Constructor c : constructors) {
			System.out.println("constructors: " + c.getName());
		}
		
		for (Class c : interfaces) {
			System.out.println("interfaces: " + c.getName());
		}
		
		for (Field ff : fields) {
			System.out.println("fields: " + ff.getName());
		}
		
		for (Method m : methods) {
			System.out.println("methods: " + m.getName());
		}
	}
}
