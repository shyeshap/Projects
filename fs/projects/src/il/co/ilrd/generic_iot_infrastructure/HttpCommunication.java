package il.co.ilrd.generic_iot_infrastructure;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import java.util.stream.Collectors;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.sun.net.httpserver.*;

public class HttpCommunication implements Communication {
	HttpExchange httpExchange;
	Peer peer;
	TasksManager tm;
	int threadsNum;
	
	public HttpCommunication(TasksManager tm, int threadsNum) {
		this.tm = tm;
		this.threadsNum = threadsNum;
	}
	
	@Override
	public void listen(String ipAddress, int httpPort) {
		System.out.println("listen");
		try {
			HttpServer httpServer = HttpServer.create(new InetSocketAddress(ipAddress, httpPort), 0);
			HttpContext context = httpServer.createContext("/requests");
			context.setHandler(this::handle);
			httpServer.start();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void handle(HttpExchange httpExchange) throws IOException {
		this.httpExchange = httpExchange;
		peer = new HttpPeer(httpExchange);
		if("GET".equals(httpExchange.getRequestMethod())) { 
		this.httpExchange = httpExchange;
			handleGetRequest();
		}else if("POST".equals(httpExchange.getRequestMethod())) { 
			handlePostRequest();        
		}
	}

	private void handleGetRequest() {
		Response response = new Response(405, "SC_METHOD_NOT_ALLOWED");
		peer.send(response);
	}

	private void handlePostRequest() {
		JsonObject body = getbody();
		tm.createAndSubmitTask(body, peer);
	}
	
	private JsonObject getbody() {
		String jsonStr = null;
		try(InputStream inputStream = httpExchange.getRequestBody();
				BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));){
			jsonStr = reader.lines().collect(Collectors.joining());
			System.out.println(jsonStr);
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return new JsonParser().parse(jsonStr).getAsJsonObject();
	}
}
