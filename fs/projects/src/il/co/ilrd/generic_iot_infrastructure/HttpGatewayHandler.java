package il.co.ilrd.generic_iot_infrastructure;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URI;

import com.google.gson.Gson;
import com.sun.net.httpserver.*;

import il.co.ilrd.generic_iot_infrastructure.msg.*;


public class HttpGatewayHandler implements HttpHandler, Communication {
	private static final int HTTP_OK_STATUS = 200;
	private static final int SC_METHOD_NOT_ALLOWED = 405;
	//private static final int HTTP_CLIENT_ERROR = 400;
	//private static final int HTTP_SERVER_ERROR = 500;

	//private static final String AND_DELIMITER = "&";
	//private static final String EQUAL_DELIMITER = "=";
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
		Response response = new Response(SC_METHOD_NOT_ALLOWED, "SC_METHOD_NOT_ALLOWED");
		peer.send(response);
	}

	private void handlePostRequest() {
		Gson gson = new Gson();
		InputStream inputStream = httpExchange.getRequestBody();
		BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
		Msg msg = gson.fromJson(reader, Msg.class);
		tm.createAndSubmitTask(msg, peer);
	}
	
	private static void printRequestInfo(HttpExchange exchange) throws IOException {
		System.out.println("-- headers --");
		Headers requestHeaders = exchange.getRequestHeaders();
		requestHeaders.entrySet().forEach(System.out::println);

		System.out.println("-- principle --");
		HttpPrincipal principal = exchange.getPrincipal();
		System.out.println(principal);

		System.out.println("-- HTTP method --");
		String requestMethod = exchange.getRequestMethod();
		System.out.println(requestMethod);

		System.out.println("-- query --");
		URI requestURI = exchange.getRequestURI();
		String query = requestURI.getQuery();
		System.out.println(query);

	}

	@Override
	public void listen() {
		// TODO Auto-generated method stub
		
	}

}
