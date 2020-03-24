package il.co.ilrd.multithreaded_counting_sort;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Stream;

public class FileToArray {

	public static char[] fileToArray(String filePath) 
	{
		StringBuilder contentBuilder = new StringBuilder();
		 
        try (Stream<String> stream = Files.lines( Paths.get(filePath), StandardCharsets.UTF_8)) 
        {
            stream.forEach(s -> contentBuilder.append(s).append("\n"));
        }
        catch (IOException e) 
        {
            e.printStackTrace();
        }
	    
	    String str = contentBuilder.toString();
	    str = str.replaceAll("\\s+","");
	    
	    return str.toCharArray(); 
	}
}
