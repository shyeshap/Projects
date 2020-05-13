package il.co.ilrd.networking;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class PingServer {
	private static final int PORT = 50000;
	static boolean flaga = true;
	private static String str = "PONG";

	private static ServerSocket serverSocket;
	private static Socket clientSocket;

	public static void main(String[] args) throws IOException
	{
	    serverSocket = null;
	    try
	    {
	        serverSocket = new ServerSocket(PORT);
	    }
	    catch(IOException e)
	    {
	        System.err.println("Could not listen on port: " + PORT);
	        System.exit(1);
	    }

	    System.out.print("Wating for connection...");

	    clientSocket = null;
	    try
	    {
	        clientSocket = serverSocket.accept();
	        System.out.println("Connection established");
	        flaga = false;
	    }
	    catch(IOException e)
	    {
	        System.err.println("Accept failed.");
	        System.exit(1);
	    }
	    
	    final DataOutputStream out = new DataOutputStream(clientSocket.getOutputStream());
	    final DataInputStream in = new DataInputStream(clientSocket.getInputStream());
	    str = str.length() + str;
	    int ret = 0;

	    for (int i = 0; i < 3; ++i) {
	    	int loop = in.read() - 48;
	    	for (int j = 0; j < loop; ++j) {
	    		ret = in.read();
	    		System.out.print((char)ret);
	    	}
	    	System.out.println();
	    	out.writeBytes(str); 
	    }
	    
	    out.close();
	    in.close();
	    serverSocket.close();
	}
}