package il.co.ilrd.singleton;

import static org.junit.Assert.*;
import org.junit.jupiter.api.Test;

class SingletonTest {
	
	@Test
	void test() {
		long start;
		long finish;
		
		//1
		start = System.nanoTime();
		Singleton s1 = Singleton.ThreadSafeSynchronization();
		for (int i = 0; i < 100; ++i) {
			assertTrue(s1 == Singleton.ThreadSafeSynchronization());
		}
		finish = System.nanoTime();
		System.out.println("1. time: " + (finish - start));
		
		//2
		start = System.nanoTime();
		Singleton s2 = Singleton.DoubleCheckedVolatileSingleton();
		for (int i = 0; i < 100; ++i) {
			assertTrue(s2 == Singleton.DoubleCheckedVolatileSingleton());
		}    		
		finish = System.nanoTime();
		System.out.println("2. time: " + (finish - start));
		
		//3
		start = System.nanoTime();
		Singleton s3 = Singleton.getNotLazySingleton();
		for (int i = 0; i < 100; ++i) {
			assertTrue(s3 == Singleton.getNotLazySingleton());
		}
		finish = System.nanoTime();
		System.out.println("3. time: " + (finish - start));   
		
		//4
		start = System.nanoTime();
		Singleton s4 = Singleton.getInstance();
		for (int i = 0; i < 100; ++i) {
			assertTrue(s4 == Singleton.getInstance());
		}
		finish = System.nanoTime();
		System.out.println("4. time: " + (finish - start)); 
		
		start = System.nanoTime();
		SingletonEnum instance = SingletonEnum.INSTANCE;       
		for (int i = 0; i < 100; ++i) {
	       	assertTrue(instance == SingletonEnum.INSTANCE);
		}
		finish = System.nanoTime();
		System.out.println("5. time: " + (finish - start));  
	
	}
}
