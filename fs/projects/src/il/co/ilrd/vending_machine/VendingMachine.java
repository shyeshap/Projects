package il.co.ilrd.vending_machine;

public class VendingMachine {
	private double balance = 0.0;
	private State state;
	
	MonitorIMP monitor = new MonitorIMP();
	
	public VendingMachine() {
		state = State.WAIT_FOR_COIN;
	}
		
	private void returnChange() { 
		monitor.print("Dont forget your change of " + String.valueOf(balance) + "$");
		balance = 0.0;
	}
	
	public void insertCoin(double coin) {
		balance += coin;
		state = state.gotCoin();
	}
	
	public void order(String drink) {
		Product product = Product.valueOf(drink);
		monitor.print(String.valueOf(product.getStock()) + " " + product.toString() + "s are in stock");
		monitor.print(product.toString() + " is " + String.valueOf(product.getPrice()) + "$");
		monitor.print("You have inserted " +  String.valueOf(balance) + "$");
		
		if (state == State.WAIT_FOR_COIN) {
			return;
		}
		
		else if ((product.getPrice() <= balance) && (product.getStock() > 0)){
			balance -= product.getPrice();
			product.setStock(product.getStock() - 1);
			monitor.print("Take your " + product.toString());
		}
		
		returnChange();
		state = state.gotOrder();
	}

	private enum State {
		WAIT_FOR_COIN,
		WAIT_FOR_ORDER;

		public State gotCoin() {return State.WAIT_FOR_ORDER;}
		public State gotOrder() {return State.WAIT_FOR_COIN;}
	}
	
	public class MonitorIMP implements Monitor {

		@Override
		public void print(String str) {
			System.out.println(str);
		}

	}
}