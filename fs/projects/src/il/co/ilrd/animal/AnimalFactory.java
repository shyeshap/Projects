package il.co.ilrd.animal;

public class AnimalFactory {
	String color;
	int numLegs;
	
	public AnimalFactory(String color, int numLegs) {
		this.color = color;
		this.numLegs = numLegs;
	}
	
	public Dog getDog() {
		System.out.print(numLegs + " legged ");
		return new Dog(this);
	}
	
	public Cat getCat() {
		System.out.print(numLegs + " legged ");
		return new Cat(this);
	}
	
	public Bird getBird() {
		System.out.print(numLegs + " legged ");
		return new Bird(this);
	}
}
