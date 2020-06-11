package il.co.ilrd.quizzes;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class Quiz7 {
	public static void main(String []args){
        Map<String, String> phone = new HashMap<String, String>();
        phone.put("apple", "iphone");
        phone.put("HTC", "one");
        phone.put("samsung", "S5");
        
        Iterator iterator = phone.keySet().iterator();
        
        while (iterator.hasNext()){
            System.out.println(phone.get(iterator.next()));
            phone.put("Sony", "z");
        }
    }
}
