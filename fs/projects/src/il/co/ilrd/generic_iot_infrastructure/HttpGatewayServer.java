package il.co.ilrd.generic_iot_infrastructure;

import java.io.IOException;
import java.net.InetSocketAddress;

import com.sun.net.httpserver.HttpContext;
import com.sun.net.httpserver.HttpServer;


public class HttpGatewayServer {
	
	public static void main(String[] args) {

		HttpServer server;
		try {
			TasksManager tm = new TasksManager();
			new CommandLoader();
			server = HttpServer.create(new InetSocketAddress("10.1.0.5", 8080), 0);
			HttpContext context = server.createContext("/demo");
			context.setHandler(new HttpGatewayHandler(tm));
			server.start();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
