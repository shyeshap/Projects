package il.co.ilrd.animal;

public class Bird extends Animal {
	String color;
	int numLegs;
	
	public Bird(AnimalFactory args) {
		this.color = args.color;
		this.numLegs = args.numLegs;
		System.out.println(color + " Bird Ctor");
	}
	
	@Override
	public void makeSound() {
		System.out.println("Squik");
	}

}
