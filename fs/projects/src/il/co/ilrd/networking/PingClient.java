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
	private static byte[] message = new byte[1600];

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
		str = str.length() + str;

		int ret = 0;
		for (int i = 0; i < 3; ++i) {
			out.writeBytes(str);
			int loop = in.read() - 48;
			for (int j = 0; j < loop; ++j) {
	    		ret = in.read();
	    		System.out.print((char)ret);
	    	}
	    	System.out.println();
		}

		out.close();
		in.close();
		socket.close();
	}
}