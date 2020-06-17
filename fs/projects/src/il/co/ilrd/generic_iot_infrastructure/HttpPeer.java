package il.co.ilrd.generic_iot_infrastructure;

import java.io.IOException;
import java.io.OutputStream;

import com.sun.net.httpserver.HttpExchange;

public class HttpPeer implements Peer{
	private HttpExchange httpExchange;
	
	public HttpPeer(HttpExchange httpExchange) {
		this.httpExchange = httpExchange;
	}

	public HttpExchange getHttpExchange() {
		return httpExchange;
	}

	public void setHttpExchange(HttpExchange httpExchange) {
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
