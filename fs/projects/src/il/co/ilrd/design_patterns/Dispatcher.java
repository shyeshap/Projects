package il.co.ilrd.design_patterns;

import java.util.LinkedList;
import java.util.List;
import java.util.function.Consumer;

public class Dispatcher<T> {
	
	private List<Callback<T>> callbackList = new LinkedList<>();
	
	public void register(Callback<T> cb) {
		cb.dispatcher = this;
		callbackList.add(cb);
	}
	
	public void stopAll() {
		for (Callback<T> callback : callbackList) {
			callback.notifyDeath();
		}
	}
	
	public void updateAll(T msg) {
		for (Callback<T> callback : callbackList) {
			callback.update(msg);
		}
	}
	
	public static class Callback<T> {
		private Consumer<T> c;
		private Runnable r;
		Dispatcher<T> dispatcher;
		
		public Callback(Consumer<T> c, Runnable r) {
			this.c = c;
			this.r = r;
		}
		
		private void update(T t) {
			c.accept(t);
		}	
		
		private void notifyDeath() {
			r.run();
		}
		
		public boolean stopService() {
			return dispatcher.callbackList.remove(this);
		}
	}
}
