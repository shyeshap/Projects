package il.co.ilrd.generic_iot_infrastructure;

import java.io.IOException;
import java.io.OutputStream;

import com.sun.net.httpserver.HttpExchange;

import il.co.ilrd.generic_iot_infrastructure.msg.Response;

public class HttpPeer implements Peer{
	HttpExchange httpExchange;
	
	public HttpPeer(HttpExchange httpExchange) {
		this.httpExchange = httpExchange;
	}

	@Override
	public void send(Response response) {
		System.out.println("send");
		String responseStr = response.ToString();
		OutputStream outputStream = httpExchange.getResponseBody();		
		try {
			httpExchange.sendResponseHeaders(response.getStatusCode(), responseStr.length());
			outputStream.write(responseStr.getBytes());
			outputStream.flush();
			outputStream.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
