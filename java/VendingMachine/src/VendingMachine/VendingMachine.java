package VendingMachine;

public class VendingMachine {
	private double balance = 0.0;
	private State state;
	private Monitor monitor;
	
	public VendingMachine(Monitor monitor, int[] stock) {
		state = State.WAIT_FOR_COIN;
		this.monitor = monitor;
		
		for(Product item : Product.values()) {
			item.setStock(stock[item.ordinal()]);
		}
	}
		
	public void returnChange() { 
		monitor.print("Dont forget your change of " + Strinmonig.valueOf(balance) + "$");
		balance = 0.0;
	}
	
	public void insertCoin(double coin) {
		balance += coin;
		state = state.gotCoin();
	}
	
	public void order(int key) {
		Product product;
		
		for(Product item : Product.values()) {
			if(item.getKey() == key) {
				product = item;
			}
		}
		
		state = state.gotOrder(monitor, product);
	}

	private enum State {
		WAIT_FOR_COIN{
			@Override
			public abstract State gotOrder(Monitor monitor, Product product) {
				monitor.print(product.toString() + " is " + String.ValueOf(product.getPrice()) + "$");
				
				return WAIT_FOR_COIN;
			}
		},
		
		WAIT_FOR_ORDER {
			@Override
			public abstract State gotOrder(Monitor monitor, Product product) {
				monitor.print("You have inserted " +  String.valueOf(balance) + "$");
				
				if (product.getStock() == 0) {
					monitor.print("No " + product.toString() + "s in stock, please choose different product");
					
					return WAIT_FOR_ORDER;
				}
				
				if (product.getPrice() > balance) {
					monitor.print("Insert " + String.valueOf(product.getPrice() - balance) "$ more");
					
					return WAIT_FOR_COIN;
				}
					
				balance -= product.getPrice();
				product.setStock(product.getStock() - 1);
				monitor.print("Take your " + product.toString());
				returnChange();
				
				return WAIT_FOR_COIN;
			}
		};
		
		private State state;
		
		public State gotCoin() {
			return WAIT_FOR_ORDER;
		}
		public abstract State gotOrder(Monitor monitor, int key);
	}
}
