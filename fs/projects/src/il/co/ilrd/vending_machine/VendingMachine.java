package il.co.ilrd.vending_machine;

public class VendingMachine {
	private State state;
	private double balance;
	private Monitor msg;
	private int[] stock;
	
	public VendingMachine(Monitor monitorImp, int[] stock) {
		this.stock = stock;
		msg = monitorImp;
		state = State.INIT;
	}
	public void startMachine() {
		
		state = State.WAIT_FOR_COIN;
	}
	public void getBalance() {msg.print("Money inserted: " + balance);}
	public void insertCoin(double money) {
		state.gotCoin(this, money);
	}
	
	private Product findProduct(int key) {
		for(Product productKey: Product.values()) {
			if(productKey.getKey() == key) {
				return productKey;
			}
		}
		return null;
	}
	
	public void order(int key) {
		Product pick = findProduct(key);
		if(null == pick) {
			msg.print("Wrong key input");
		}
		else {
			state.gotOrder(this, pick);			
		}
	}

	private enum State{
		INIT{
			@Override
			public void gotCoin (VendingMachine VM, double money) {};
			@Override
			public void gotOrder (VendingMachine VM, Product pick) {};
		},
		WAIT_FOR_COIN{
			@Override
			public void gotCoin (VendingMachine VM, double money) {
				VM.balance += money;
				VM.state = WAIT_FOR_ORDER;
			}
			@Override
			public void gotOrder (VendingMachine VM, Product pick) {
				VM.msg.print("Price of " + pick.name() + " is " + pick.getPrice());
			}
		},
		WAIT_FOR_ORDER{
			@Override
			public void gotCoin (VendingMachine VM, double money) {
				VM.balance += money;
			}
			@Override
			public void gotOrder (VendingMachine VM, Product pick) {
				double change = VM.balance;
				
				if(VM.stock[pick.ordinal()] < 1) {
					VM.msg.print("Out of Stock");
				}
				else if(pick.price < VM.balance) {
					change -= pick.price;
					VM.msg.print("Thank you for buying " + pick.name());
					--VM.stock[pick.ordinal()];			
				}
				VM.msg.print("Your change is " + change + " Shmekels");
				VM.balance = 0;
				VM.state = WAIT_FOR_COIN;
			}
		};
		
		public abstract void gotCoin(VendingMachine VM, double money);
		public abstract void gotOrder(VendingMachine VM, Product pick);		
	}
	
	private enum Product{
		COLA(1,5),
		TUT(2,6),
		ZERO(3,9),
		TEA(4,4),
		WATER(5,3),
		SPRITE(6,7);
		
		private final int key;
		private double price;
		
		private Product(int key, double price) {
			
			this.price = price;
			this.key = key;
		}
		public int getKey() {return key;}
		public double getPrice() {return price;}
	}
}