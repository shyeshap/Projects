package testClass;

public class testClass {

	public static void main(String[] args) {
    	try {
    	Class cl = Class.forName(args[0]);
    	System.out.println("Name: " + cl.getName());
		System.out.println("class: " + args[0]);
		System.out.println("classes: " + cl.getClasses());
		System.out.println("annotations: " + cl.getAnnotations());
		System.out.println("constructor: " + cl.getConstructors());
		System.out.println("Feilds: " + cl.getFields());
		System.out.println("Methods: " + cl.getMethods());
		System.out.println("modifiers: " + cl.getModifiers());

    	}
    	catch(ClassNotFoundException ex) {
            System.out.println(ex.toString());
         }
	}

}
