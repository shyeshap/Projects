package il.co.ilrd.generic_iot_infrastructure;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import com.sun.net.httpserver.Authenticator;
import com.sun.net.httpserver.Filter;
import com.sun.net.httpserver.HttpContext;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import sun.net.httpserver.AuthFilter;

/**
 * HttpContext represents a mapping between a protocol (http or https) together with a root URI path
 * to a {@link HttpHandler} which is invoked to handle requests destined
 * for the protocol/path on the associated HttpServer.
 * <p>
 * HttpContext instances are created by {@link HttpServer#createContext(String,String,HttpHandler,Object)}
 * <p>
 */
public class HttpGatewayContext extends HttpContext {

    private String path;
    private String protocol;
    private HttpHandler handler;
    private Map<String,Object> attributes = new HashMap<String,Object>();
    private HttpGatewayServer server;
    /* system filters, not visible to applications */
    private LinkedList<Filter> sfilters = new LinkedList<Filter>();
    /* user filters, set by applications */
    private LinkedList<Filter> ufilters = new LinkedList<Filter>();
    private Authenticator authenticator;
    private AuthFilter authfilter;
    
    /**
     * constructor is package private.
     */
    HttpGatewayContext (String protocol, String path, HttpHandler cb, HttpGatewayServer server) {
        if (path == null || protocol == null || path.length() < 1 || path.charAt(0) != '/') {
            throw new IllegalArgumentException ("Illegal value for path or protocol");
        }
        this.protocol = protocol.toLowerCase();
        this.path = path;
        if (!this.protocol.equals("http") && !this.protocol.equals ("https")) {
            throw new IllegalArgumentException ("Illegal value for protocol");
        }
        this.handler = cb;
        this.server = server;
        authfilter = new AuthFilter(null);
        sfilters.add (authfilter);
    }
    
	@Override
	public Map<String, Object> getAttributes() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Authenticator getAuthenticator() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public List<Filter> getFilters() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public HttpHandler getHandler() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String getPath() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public HttpServer getServer() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Authenticator setAuthenticator(Authenticator arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void setHandler(HttpHandler arg0) {
		// TODO Auto-generated method stub

	}

}
