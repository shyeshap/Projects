package il.co.ilrd.vending_machine;

public class VendingMachine {
	private double balance = 0.0;
	private State state;
	private Monitor monitor;
	int[] stock;
	
	public VendingMachine(Monitor monitor, int[] stock) {
		state = State.WAIT_FOR_COIN;
		this.monitor = monitor;
		this.stock = stock;
	}
		
	public void returnChange() { 
		monitor.print("Dont forget your change of " + String.valueOf(balance) + "$");
		balance = 0.0;
	}
	
	public void insertCoin(double coin) {
		balance += coin;
		state = state.gotCoin(this);
	}
	
	public void order(int key) {
		Product product = null;
		
		for(Product item : Product.values()) {
			if(item.ordinal() == key) {
				product = item;
				this.state = state.gotOrder(this, product);
				
				return;
			}
		}
		
		monitor.print("Unrecognized key. Please try again");
	}

	private enum State {
		WAIT_FOR_COIN {
			@Override
			public State gotOrder(VendingMachine vm, Product product) {
				vm.monitor.print(product.toString() + " is " + String.valueOf(product.getPrice()) + "$");
				
				return WAIT_FOR_COIN;
			}
		},
		
		WAIT_FOR_ORDER {
			@Override
			public State gotOrder(VendingMachine vm, Product product) {
				vm.monitor.print("Place your order");
				
				if (vm.stock[product.ordinal()] == 0) {
					vm.monitor.print("No " + product.toString() + "s in stock, please choose different product");
					
					return WAIT_FOR_ORDER;
				}
				
				if (product.getPrice() > vm.balance) {
					vm.monitor.print("Insert " + String.valueOf(product.getPrice() - vm.balance) + "$ more for " + product.toString());
					
					return WAIT_FOR_COIN;
				}
					
				vm.balance -= product.getPrice();
				vm.stock[product.ordinal()] -= 1;
				vm.monitor.print("Take your " + product.toString());
				vm.returnChange();
				
				return WAIT_FOR_COIN;
			}
		};
		
		public abstract State gotOrder(VendingMachine vm, Product product);

		public State gotCoin(VendingMachine vm) {
			vm.monitor.print("Please insert coin");
			vm.monitor.print("You have inserted " +  String.valueOf(vm.balance) + "$");
			return WAIT_FOR_ORDER;
		}
	}
}