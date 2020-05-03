package il.co.ilrd.tests;

import org.junit.jupiter.api.Test;

import il.co.ilrd.design_patterns.Dispatcher;
import il.co.ilrd.fire_observer.*;

class DispatcherTest {

	@Test
	void test() {
		Dispatcher<String> disp = new Dispatcher<>();
		FireDetector fd = new FireDetector(disp);
		Guard g1 = new Guard(disp, "g1");
		Guard g2 = new Guard(disp, "g2");
		
		fd.fireHandle();
		g1.signOut();
		fd.fireHandle();
		fd.outOfOrderNotify();
		
		Sprinkler s1 = new Sprinkler(disp, 1);
		Sprinkler s2 = new Sprinkler(disp, 2);
		
		fd.fireHandle();
		fd.outOfOrderNotify();
	}

}
