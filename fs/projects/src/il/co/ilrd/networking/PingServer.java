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
	private static char[] buff = new char[1600];

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
	    
	    for (int i = 0; i < 3; ++i) { 	
	    	int loop = (int)in.readInt();
	    	for (int j = 0; j < loop; ++j) {
	    		buff[j] = (char)in.read();
	    	}
	    	System.out.println(buff);
	    	
	    	out.writeInt(str.length());
	    	out.writeBytes(str); 
	    }
	    
	    out.close();
	    in.close();
	    serverSocket.close();
	}
}