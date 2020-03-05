import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class RuntimeInvestigation { 

    public static void main(String[] args) 
    { 
      int num_of_ints = 100000; 
      int num_of_arrays = 1000;

     	Runtime r = Runtime.getRuntime();  
 	
		  ArrayList<int[]> list = new ArrayList<int[]>();

 		 while (true)
 		 {
 			//list.add(new int[num_of_ints]);

 			System.out.println("Free Memory: "+r.freeMemory()); 
  			System.out.println("Total Memory: "+r.totalMemory());
     }

   }
}
