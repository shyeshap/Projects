package il.co.ilrd.vending_machine;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

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
		Monitor monitor = new MonitorIMP();
		VendingMachine vMachine = new VendingMachine(monitor, stock);
		
		vMachine.insertCoin(10);
		vMachine.order("COLA");
		
		vMachine.insertCoin(4);
		vMachine.order("TEA");
		
		vMachine.insertCoin(15);
		vMachine.order("TEA");
		
		vMachine.insertCoin(13);
		vMachine.order("TEA");
		
		vMachine.insertCoin(20);
		vMachine.order("TEA");
		
		
	}

}