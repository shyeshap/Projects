package il.co.ilrd.vending_machine;

public enum Product {
	COLA	(10),
	TUTIT	(2),
	ZERO	(7),
	TEA		(13),
	WATER	(5),
	SPRITE	(3);
	
	private double price;
	
	private Product(double price) {
		this.price = price;
	}
	
	public double getPrice() {return price;}
}