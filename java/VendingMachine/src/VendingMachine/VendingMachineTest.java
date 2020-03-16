package VendingMachine;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class VendingMachineTest {

	@Test
	void test() {
		VendingMachine vMachine = new VendingMachine();
		
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
