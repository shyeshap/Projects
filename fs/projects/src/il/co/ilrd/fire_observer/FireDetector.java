package il.co.ilrd.fire_observer;

import il.co.ilrd.design_patterns.Dispatcher;

public class FireDetector {
	private Dispatcher<String> disp;
	
	public FireDetector(Dispatcher<String> disp) {
		this.disp = disp;
	}
	
	public void outOfOrderNotify() {
		disp.stopAll();
	}
	
	public void fireHandle() {
		System.out.println("FIRE ALARM!!!");
		disp.updateAll("FIRE ALARM!!!");
	}
}
