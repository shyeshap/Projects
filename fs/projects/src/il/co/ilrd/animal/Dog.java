package il.co.ilrd.animal;

public class Dog extends Animal {
	String color;
	int numLegs;
	
	public Dog(AnimalFactory args) {
		this.color = args.color;
		this.numLegs = args.numLegs;
		System.out.println(color + " Dog Ctor");
	}
	
	public static Dog getInstance(AnimalFactory args) {
		return new Dog(args);
	}

	
	@Override
	public void makeSound() {
		System.out.println("woooof");
	}

}
