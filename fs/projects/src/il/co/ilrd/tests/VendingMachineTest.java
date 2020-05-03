package il.co.ilrd.tests;

import org.junit.jupiter.api.Test;

import il.co.ilrd.vending_machine.Monitor;
import il.co.ilrd.vending_machine.VendingMachine;

class VendingMachineTest {
	
	public class MonitorIMP implements Monitor {

		@Override
		public void print(String str) {
			System.out.println(str);
		}

	}
	
	@Test
	void test() {
		int[] stock = {3,2,1,6,5,4};
		int[] stock2 = {2,4,6,2,6,3};
		Monitor monitor = new MonitorIMP();
		
		VendingMachine vMachine = new VendingMachine(monitor, stock);
		VendingMachine vMachine2 = new VendingMachine(monitor, stock2);

		vMachine.insertCoin(10);
		vMachine.order(1);
		
		vMachine.insertCoin(4);
		vMachine.order(3);
		
		vMachine.insertCoin(15);
		vMachine.order(2);
		
		vMachine.insertCoin(13);
		vMachine.order(2);
		
		vMachine.returnChange();
		
		vMachine.insertCoin(20);
		vMachine.order(6);
		
		vMachine.order(3);
		
		vMachine2.insertCoin(222);
		vMachine2.order(2);
	
	}

}