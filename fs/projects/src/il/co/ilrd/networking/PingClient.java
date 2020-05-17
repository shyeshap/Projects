package il.co.ilrd.networking;

/* Client.java */
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class PingClient
{
	private static final int PORT = 50000;
	private static final String HOST = "localhost";
	private static String str = "PING";
	private static char[] buff = new char[1600];

	public static void main(String[] args) throws IOException
	{
		System.out.println("client started");

		Socket socket = null;
		try
		{
			socket = new Socket(HOST, PORT);
		} catch(Exception e)
		{
			System.err.println("Could not connect to " + HOST + ": " + PORT);
			System.exit(1);
		}

		final DataOutputStream out = new DataOutputStream(socket.getOutputStream());
		final DataInputStream in = new DataInputStream(socket.getInputStream());
		int len = str.length();
		for (int i = 0; i < 3; ++i) {
			out.writeInt(len);
			out.writeBytes(str);
			
			int loop = (int)in.readInt();
			for (int j = 0; j < loop; ++j) {
	    		buff[j] = (char)in.read();
	    	}
	    	System.out.println(buff);
		}

		out.close();
		in.close();
		socket.close();
	}
}