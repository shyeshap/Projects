package il.co.ilrd.fire_observer;

import java.util.function.Consumer;

import il.co.ilrd.design_patterns.Dispatcher;
import il.co.ilrd.design_patterns.Dispatcher.Callback;

public class Sprinkler {
	private int num;
	private Runnable r = () -> System.out.println("sprinkler " + num + ": notify death");
	private Consumer<String> c = s -> System.out.println("sprinkler " + num + " ON");
	private Callback<String> call = new Dispatcher.Callback<String>(c, r);
	
	public Sprinkler(Dispatcher<String> disp, int num) {
		this.num = num;
		disp.register(call);
	}
	
	public void dettach() {
		call.stopService();
	}
	
	public void signOut() {
		call.stopService();
	}
}
