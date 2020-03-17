package il.co.ilrd.singleton;

public class Singleton {
	private static Singleton singleton;
	private volatile static Singleton volatileSingleton; //volatile instance
    private static final Singleton notLazySingleton = new Singleton(); //the variable will be created when the class is loaded
    
    private Singleton (){}
    
    //A thread-safe singleton pattern in java using Synchronization
	public synchronized static Singleton ThreadSafegetInstance() {
	   if(singleton == null) {
	      singleton = new Singleton();
	   }
	   return singleton;
	}
	
	//Double-checking locking
	public static Singleton DoubleCheckedgetInstance() {
	  if(singleton == null) {
	     synchronized(Singleton.class) {
	       if(singleton == null) {
	         singleton = new Singleton();
	       }
	    }
	  }
	  return singleton;
	}
	
	//Double-checking locking with volatile keyword	
    public static Singleton volatileSingleton() {
        if (volatileSingleton == null) {                         
            synchronized (Singleton.class) {
                if (volatileSingleton == null) {       
                	volatileSingleton = new Singleton();
                }
            }
        }
        return volatileSingleton;
    }

    //Thread-safe but not lay initialized 
    //static final variable
    public static Singleton getNotLazySingleton(){
            return notLazySingleton;
    }
    
    //The ultimate Thread-safe and efficient singleton pattern in Java
    // Correct lazy initialization in Java 
    private static class SingletonHolder {
        public static Singleton bestSingleton = new Singleton();
     }
    
    public static Singleton getInstance() {
        return SingletonHolder.bestSingleton;
    }
    
    //Using Enum
    //The best way to implement a thread safe Singleton Pattern in Java is using Enum.
    enum Color {
    	 
        RED(1), GREEN(2), YELLOW(3);
     
        private int nCode ;
     
        private Color(int _nCode) {
            this.nCode = _nCode;
        }
     
        @Override
     
        public String toString() {
            return String.valueOf (this.nCode);
        }
     
    }
     
    public class ColorTest {
        public void main(String[] args) {
            Color red = Color.RED;
            Color red2 = Color.RED;
     
            System.out.println(red == red2); // return true
     
        }
    }

}