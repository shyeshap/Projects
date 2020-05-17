package il.co.ilrd.tests;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.ArrayList;

import junit.framework.TestCase;

public class ChatClient extends TestCase {
	private static String host = "localhost";
	private static int serverPortNum = 11111;
	
	public static void main(String[] args) throws IOException, InterruptedException {

		InetSocketAddress socketAddr = new InetSocketAddress(host, serverPortNum);
		SocketChannel clientChannel = SocketChannel.open(socketAddr);

		log("Connecting to Server on port 1111...");

		ArrayList<String> chat = new ArrayList<String>();

		// create a ArrayList with companyName list
		chat.add("LOG_IN[shyesh@gmail.com][ShyeShu]");
		chat.add("CREATE_GROUP[123][fs8081]");
		chat.add("JOIN_GROUP[123][100]");
		chat.add("LEAVE_GROUP[123][100]");
		chat.add("SEND_MSG[123][100][msg]");
		chat.add("LOG_OUT[]");
		
		for (String companyName : chat) {

			byte[] message = new String(companyName).getBytes();
			ByteBuffer buffer = ByteBuffer.wrap(message);
			clientChannel.write(buffer);

			log("sending: " + companyName);
			buffer.clear();

			// wait for 2 seconds before sending next message
			Thread.sleep(5000);
		}
		
		
		
	}

	private static void log(String str) {
		System.out.println(str);
	}
}
