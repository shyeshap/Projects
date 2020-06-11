package il.co.ilrd.tests;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.ArrayList;
import java.util.Scanner;
import il.co.ilrd.chat_server.*;
import junit.framework.TestCase;

public class ChatClient extends TestCase {
	private static String host = "localhost";
	private static int serverPortNum = 11111;
	
	public static void main(String[] args) throws IOException, InterruptedException {

		InetSocketAddress socketAddr = new InetSocketAddress(host, serverPortNum);
		SocketChannel clientChannel = SocketChannel.open(socketAddr);

		log("Connecting to Server on port 1111...");
		
	/*	RequestLogin login = new RequestLogin("shyesh@gmail.com", "ShyeShu");
		
		try (ObjectOutputStream out = new ObjectOutputStream(clientChannel.socket().getOutputStream())) {
			out.writeObject(login);
		} catch (IOException e) {
			e.printStackTrace();
		}*/
	}
		
		// create a ArrayList with companyName list
		//chat.add("LOG_IN[shyesh@gmail.com][ShyeShu]");
		//chat.add("CREATE_GROUP[1][fs8081]");
		//chat.add("JOIN_GROUP[1][1]");
		//chat.add("LEAVE_GROUP[1][1]");
		//chat.add("SEND_MSG[1][1][msg]");
		//chat.add("LOG_OUT[]");
		
		//RequestLogin login = new RequestLogin("shyesh@gmail.com", "ShyeShu");
		/*
		Thread out = new Thread(() -> {
			
			while (true) {
				Scanner input  = new Scanner(System.in);
				String msg = input.nextLine();
				byte[] message = new String(msg).getBytes();
				ByteBuffer buffer = ByteBuffer.wrap(message);
				try {
					clientChannel.write(buffer);
				} catch (IOException e) {
					e.printStackTrace();
				}

				log("sending: " + msg);
				buffer.clear();

				// wait for 2 seconds before sending next message
				try {
					Thread.sleep(2000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		});
	
		Thread in = new Thread(() -> {
			while (true) {
				
			}
		});
		
		out.start();
		in.start();
		
		out.join();
		in.join();
		
	}
*/
	private static void log(String str) {
		System.out.println(str);
	}
}
