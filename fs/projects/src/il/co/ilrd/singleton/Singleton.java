package il.co.ilrd.singleton;

public class Singleton {
	private static Singleton singleton;
	private volatile static Singleton volatileSingleton; //volatile instance
    private static final Singleton notLazySingleton = new Singleton(); //the variable will be created when the class is loaded
       
    private Singleton (){}
    
    //A thread-safe singleton pattern in java using Synchronization
	public synchronized static Singleton ThreadSafeSynchronization() {
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

    //Thread-safe but not lazy initialized 
    //static final variable
    public static Singleton getNotLazySingleton(){
            return notLazySingleton;
    }
   
/*    //The ultimate Thread-safe and efficient singleton pattern in Java
    // Correct lazy initialization in Java 
    private static class LazyHolder {
        static final Singleton INSTANCE = new Singleton();
    }    
    
    public static Singleton getInstance() {
        return LazyHolder.INSTANCE;
    }*/

    
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
    
    public static class Main{
    	public static void main(String[] vars) {
    		Singleton s1 = ThreadSafeSynchronization();
    		for (int i = 0; i < 100; ++i) {
    			System.out.println(s1 == ThreadSafeSynchronization());
    		}
    		
    		System.out.println();
    		
    		Singleton s2 = DoubleCheckedgetInstance();
    		for (int i = 0; i < 100; ++i) {
    			System.out.println(s2 == DoubleCheckedgetInstance());
    		}
    		
    		System.out.println();
    		
    		Singleton s3 = volatileSingleton();
    		for (int i = 0; i < 100; ++i) {
    			System.out.println(s3 == volatileSingleton());
    		}

    		System.out.println();
    		
    		Singleton s4 = getNotLazySingleton();
    		for (int i = 0; i < 100; ++i) {
    			System.out.println(s4 == getNotLazySingleton());
    		}
    		
    		System.out.println();
    		
   
    	   Color red = Color.RED;
    	            
    	   for (int i = 0; i < 100; ++i) {
    	       	System.out.println(red == Color.RED); // return true
    	   }
    	     
    	            
    	    

    	}
    }
}