package il.co.ilrd.generic_iot_infrastructure;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.stream.Collectors;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.sun.net.httpserver.*;

public class HttpGatewayHandler implements HttpHandler, Communication {
	HttpExchange httpExchange;
	Peer peer;
	TasksManager tm;
	
	public HttpGatewayHandler(TasksManager tm) {
		this.tm = tm;
	}
	
	@Override
	public void handle(HttpExchange httpExchange) throws IOException {
		peer = new HttpPeer(httpExchange);
		this.httpExchange = httpExchange;
		if("GET".equals(httpExchange.getRequestMethod())) { 
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
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return new JsonParser().parse(jsonStr).getAsJsonObject();
	}

	@Override
	public void listen() {
		// TODO Auto-generated method stub
		
	}

}
