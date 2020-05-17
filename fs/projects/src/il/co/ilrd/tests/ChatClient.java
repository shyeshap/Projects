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

		ArrayList<String> companyDetails = new ArrayList<String>();

		// create a ArrayList with companyName list
		companyDetails.add("LOG_IN[shyesh@gmail.com][ShyeShu]");
		companyDetails.add("CREATE_GROUP[123][fs8081]");

		for (String companyName : companyDetails) {

			byte[] message = new String(companyName).getBytes();
			ByteBuffer buffer = ByteBuffer.wrap(message);
			clientChannel.write(buffer);

			log("sending: " + companyName);
			buffer.clear();

			// wait for 2 seconds before sending next message
			Thread.sleep(2000);
		}
		clientChannel.close();
	}

	private static void log(String str) {
		System.out.println(str);
	}
}
