package il.co.ilrd.animal;

import il.co.ilrd.design_patterns.Factory;

public class Main {

	public static void main(String[] args) {
		Factory<String, Animal, AnimalFactory> f = new Factory<>();
		
/*************** constructor method reference ***************/
		f.add("Dog", Dog::new);
		f.add("Cat", Cat::new);
		f.add("Bird", animalArgs -> new Bird(animalArgs));

		Animal d = f.create("Dog", new AnimalFactory("Brown", 4));
		Animal c = f.create("Cat", new AnimalFactory("Pink", 4));
		Animal b = f.create("Bird", new AnimalFactory("Black", 2));

/*************** static method reference ********************/
		f.add("DogStatic", Dog::getInstance);
		f.add("CatStatic", Cat::getInstance);
		
		Animal c1 = f.create("CatStatic", new AnimalFactory("Orenge", 0));
		Animal d1 = f.create("DogStatic", new AnimalFactory("Lime", 9));
		
		c1.makeSound();
		d1.makeSound();
		
/**************** instance method reference ******************/
		f.add("dogInstance" , AnimalFactory::getDog);
		f.add("birdInstance" , AnimalFactory::getBird);
		
		f.create("dogInstance", new AnimalFactory("white", 3));
		f.create("birdInstance", new AnimalFactory("purple", 13));
		
	}
}
