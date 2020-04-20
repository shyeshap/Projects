package il.co.ilrd.collections;

import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class CollectionsEx {
	private static void Ex1(){
		int[] arr = new int[]{1,2,3,4};
		List<Integer> list = Arrays.stream(arr).boxed().collect(Collectors.toList());
		list.sort(null);
		System.out.println(list);
	}
	
	private static void Ex2(){
		Map<Integer, String> daysOfWeak = new LinkedHashMap<>();
		daysOfWeak.put(1, "Sunday");
		daysOfWeak.put(2, "Munday");
		daysOfWeak.put(3, "Tuseday");
		daysOfWeak.put(4, "Wednsday");
		daysOfWeak.put(5, "Thursday");
		daysOfWeak.put(6, "Friday");
		daysOfWeak.put(7, "Saturday");
		
		daysOfWeak.forEach((k, v) -> System.out.println(k + ": " + v)); 
		 
	    Set<Map.Entry<Integer, String>> st = daysOfWeak.entrySet();    
	       
		for (Map.Entry<Integer, String> day: st) {
			System.out.print(day.getKey() + ": ");
			System.out.println(day.getValue());
		}
	}
	
	public class DataObject{
		public String code;
		public int value;
		
		public DataObject(String code, int value) {
			this.code = code;
			this.value = value;
		}
	}
	
	private static void Ex3(){
		int sum = 0;
		DataObject[] arr = new DataObject[5];
		arr[0] = new CollectionsEx().new DataObject("a", 1);
		arr[1] = new CollectionsEx().new DataObject("b", 2);
		arr[2] = new CollectionsEx().new DataObject("c", 3);
		arr[3] = new CollectionsEx().new DataObject("d", 4);
		arr[4] = new CollectionsEx().new DataObject("e", 5);
		
		for (DataObject d : arr) {
			sum +=d.value;
		}
		
		System.out.println("Ex3: " + sum);
	}
	
	
	public static void main(String[] args) {
		Ex1();
		Ex2();
		Ex3();
		
	}

}
