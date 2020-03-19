package producersConsumers;

import java.util.concurrent.atomic.AtomicBoolean;

public class AtomicPingPong {
		volatile static AtomicBoolean flag = new AtomicBoolean();
	   
		public static void main(String[] args) throws InterruptedException {
	      
	    	System.out.println("Ready… Set… Go!");
	    	ProdCons ping = new ProdCons("Ping!", flag, true, false);
	    	ProdCons pong = new ProdCons("Pong!", flag, false, true);
	     
	        ping.start();
	        pong.start();
	      
	        ping.join();
	        pong.join();
	     
	        System.out.println("Done!");
	    }
		
	    static class ProdCons extends Thread {

	    	private String saying;
	        private AtomicBoolean flag;
	        private boolean expected;
	        private boolean newValue;
	        
	        public ProdCons(String saying, AtomicBoolean flag, boolean expected, boolean newValue) {
	            this.saying = saying;
	            this.flag = flag;
	            this.expected = expected;
	            this.newValue = newValue;
	        }

	        public void run() {
	            while (true) {
	                if(flag.get() == expected) {
	                	System.out.println(saying);
	                	flag.set(newValue);
	                }
	            }
	        }
	 }
}
