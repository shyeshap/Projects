package VendingMachine;

public enum Product {
	COLA	(10, 5),
	TUTIT	(2, 3),
	ZERO	(7, 1),
	TEA		(13, 2),
	WATER	(5, 10),
	SPRITE	(3, 7);
	
	private double price;
	private int stock;
	
	private Product(double price, int stock) {
		this.price = price;
		this.stock = stock;
	}
	
	public int getStock() {return stock;}
	public double getPrice() {return price;}
	public void setStock(int fillStock) {stock = fillStock;}
}
