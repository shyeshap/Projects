package il.co.ilrd.generic_iot_infrastructure;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.util.concurrent.Executor;

import com.sun.net.httpserver.HttpContext;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import sun.net.httpserver.HttpServerImpl;

public class HttpGatewayServer extends HttpServer {
	
	HttpServerImpl server;
	
	HttpGatewayServer() throws IOException {
		server = (HttpServerImpl)create();
	}

	HttpGatewayServer(InetSocketAddress addr, int backlog) throws IOException {
		server = (HttpServerImpl)create(addr, backlog);
	}

	@Override
	public void bind(InetSocketAddress addr, int backlog) throws IOException {
		server.bind(addr, backlog);
	}

	@Override
	public HttpContext createContext(String path) {
		return server.createContext(path);
	}

	@Override
	public HttpContext createContext(String path, HttpHandler handler) {
		return server.createContext(path, handler);
	}

	@Override
	public InetSocketAddress getAddress() {
		return server.getAddress();
	}

	@Override
	public Executor getExecutor() {
		return server.getExecutor();
	}

	@Override
	public void removeContext(String path) throws IllegalArgumentException {
		server.removeContext(path);
	}

	@Override
	public void removeContext(HttpContext context) {
		server.removeContext(context);
	}

	@Override
	public void setExecutor(Executor executor) {
		server.setExecutor(executor);
	}

	@Override
	public void start() {
		server.start();
	}

	@Override
	public void stop(int delay) {
		server.stop(delay);
	}
	
	public static void main(String[] args) {
		try {
			HttpServer server = new HttpGatewayServer();
			server.bind(new InetSocketAddress("localhost", 8080), 50);
			System.out.println(server.getAddress().toString());
			server.start();
			server.createContext("/http://java.sun.com/j2se/1.3/docs/guide/index.html");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
