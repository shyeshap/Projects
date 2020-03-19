package producersConsumers;

import java.util.concurrent.Semaphore;

public class SemPingPong {
    private final static Semaphore semPing = new Semaphore(1);
    private final static Semaphore semPong = new Semaphore(0);

    public static void main(String[] args) throws InterruptedException {
      
    	System.out.println("Ready… Set… Go!");
    	ProdCons ping = new ProdCons("Ping!", semPing, semPong);
    	ProdCons pong = new ProdCons("Pong!", semPong, semPing);
     
        ping.start();
        pong.start();
      
        ping.join();
        pong.join();
     
        System.out.println("Done!");
    }

    static class ProdCons extends Thread {

    	private String saying;
        private Semaphore mine;
        private Semaphore other;

        public ProdCons(String saying, Semaphore mine, Semaphore other) {
            this.saying = saying;
            this.mine = mine;
            this.other = other;
        }

        public void run() {
            while (true) {
                try {
					mine.acquire();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
                System.out.println(saying);
                other.release();
            }
        }
    }
}