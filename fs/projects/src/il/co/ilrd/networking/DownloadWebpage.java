package il.co.ilrd.networking;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;

public class DownloadWebpage {
	public static void download(String urlString) throws IOException {
		URL url = new URL(urlString);
		try(BufferedReader reader =  new BufferedReader(new InputStreamReader(url.openStream()));         
			BufferedWriter writer = new BufferedWriter(new FileWriter("/home/ol81-21/page.html"));) {      
			
			String line;
			while ((line = reader.readLine()) != null) {
				System.out.println(line);
				writer.append(line);
			}            
			System.out.println("Page downloaded.");
		} 
	}
	
	public static void main(String[] args) throws IOException {
		download("https://www.tutorialspoint.com/Download-webpage-in-Java");
	}

}
