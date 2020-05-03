package il.co.ilrd.fire_observer;

import java.util.function.Consumer;

import il.co.ilrd.design_patterns.Dispatcher;
import il.co.ilrd.design_patterns.Dispatcher.Callback;

public class Guard {
		private String name;
		private Runnable r = () -> System.out.println(name + ": notify death");
		private Consumer<String> c = s -> System.out.println(name + "! get fire distingusher!!");
		private Callback<String> call = new Dispatcher.Callback<String>(c, r);
		
		public Guard(Dispatcher<String> disp, String name) {
			this.name = name;
			disp.register(call);
		}
		
		public void dettach() {
			call.stopService();
		}
		
		public void signOut() {
			call.stopService();

		}
}
