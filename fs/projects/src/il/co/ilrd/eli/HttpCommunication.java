package il.co.ilrd.eli;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.sun.net.httpserver.HttpContext;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpServer;

public class HttpCommunication implements Communication {
	
	private HttpServer server;
	private TaskManagement taskManagement;
	
	public HttpCommunication(TaskManagement taskManagement) {
		this.taskManagement = taskManagement;
	}

	@Override
	public void listen(String ip, int port) {
		try {
			server = HttpServer.create(new InetSocketAddress(ip, port), 0);
		} catch (IOException e) {
			e.printStackTrace();
		}
	    HttpContext context = server.createContext("/");
	    context.setHandler(this::handleRequest);
	    server.start();		
	}

	private static JsonObject getbody(HttpExchange exchange) {
		InputStreamReader isr = null;
		BufferedReader br = null;
		StringBuilder str = null;
		try {
			isr =  new InputStreamReader(exchange.getRequestBody(),"utf-8");
			br = new BufferedReader(isr);
			int readByte;
			str = new StringBuilder(512);
			while ((readByte = br.read()) != -1) {
				str.append((char) readByte);
			}			
		} catch (IOException e) {
			
		} finally {
			try {
				br.close();
				isr.close();			
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		String jsonStr = str.toString();
		JsonParser parser = new JsonParser();
		JsonElement jsonElement = parser.parse(jsonStr);

		return jsonElement.getAsJsonObject();
	}
	
	private void handleRequest(HttpExchange exchange) throws IOException {
		Peer peer = new HttpPeer(exchange);

		if (!exchange.getRequestMethod().equals("POST")) {
			peer.send(new Response(400, "Bad Request"));
			return;
		}
		
		JsonObject data = getbody(exchange);
		taskManagement.createAndSubmitTask(peer, data);
	}
}
