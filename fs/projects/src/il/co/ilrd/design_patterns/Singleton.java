package il.co.ilrd.design_patterns;

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
	
	//Double-checking locking with volatile keyword	
    public static Singleton DoubleCheckedVolatileSingleton() {
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
    
    //Lazy: we can use static functions and static fields 
    //without even instantiate the class. 
    //so if we need to use static functions before we need to istantiate it we will prefer lazy. 
    
    private static class LazyHolder {
    	static final Singleton INSTANCE = new Singleton();
    }

    public static Singleton getInstance() {
    	return LazyHolder.INSTANCE;
    }
}

