package il.co.ilrd.generics;

import java.io.ObjectInputStream.GetField;
import java.util.ArrayList;
import java.util.List;

public class Generics {
	
	public static <T>void printArray(T[] arr) {
		for (T t: arr) {
			System.out.println(t);
		}
	}
	
	public static class FooReference<T>{
		private List<T> fooList;
		
		public List<T> getFooList() {
			return fooList;
		}

		public void setFooList(List<T> fooList) {
			this.fooList = fooList;
		}
		
		
	}
	
	public static void main(String[] args) {
		String[] arr1 = {"hi", "how", "are", "you"};
		Integer[] arr2 = {1,2,3,4,5,6};
		Boolean[] arr3 = {true, false, true};
		
		printArray(arr1);
		printArray(arr2);
		printArray(arr3);
		
		FooReference<String> f1 = new FooReference<>();
		FooReference<Float> f2 = new FooReference<>();
		
		f1.setFooList(new ArrayList<String>());
		f2.setFooList(new ArrayList<Float>());
		
		System.out.println(f1.getFooList());
		System.out.println(f2.getFooList());
		
		
		Class c = f1.getClass();
		System.out.println(c);
		c = f2.getClass();
		System.out.println(c);
		
	}

}
