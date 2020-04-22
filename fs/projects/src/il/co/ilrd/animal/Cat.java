package il.co.ilrd.animal;

public class Cat extends Animal {
	String color;
	int numLegs;
	
	public Cat(AnimalFactory args) {
		this.color = args.color;
		this.numLegs = args.numLegs;
		System.out.println(color + " Cat Ctor");
	}
	
	public static Cat getInstance(AnimalFactory args) {
		return new Cat(args);
	}
	
	
	@Override
	public void makeSound() {
		System.out.println("Meaooooo");
	}

}
