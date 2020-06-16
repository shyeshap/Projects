package il.co.ilrd.generic_iot_infrastructure;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.URI;

import com.sun.net.httpserver.Headers;
import com.sun.net.httpserver.HttpContext;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpPrincipal;

public class HttpGatewayExchange extends HttpExchange {

	@Override
	public void close() {
		System.out.println("close http");
		// TODO Auto-generated method stub

	}

	@Override
	public Object getAttribute(String arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public HttpContext getHttpContext() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public InetSocketAddress getLocalAddress() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public HttpPrincipal getPrincipal() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String getProtocol() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public InetSocketAddress getRemoteAddress() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public InputStream getRequestBody() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Headers getRequestHeaders() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String getRequestMethod() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public URI getRequestURI() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public OutputStream getResponseBody() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int getResponseCode() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public Headers getResponseHeaders() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void sendResponseHeaders(int arg0, long arg1) throws IOException {
		// TODO Auto-generated method stub

	}

	@Override
	public void setAttribute(String arg0, Object arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void setStreams(InputStream arg0, OutputStream arg1) {
		// TODO Auto-generated method stub

	}

}
