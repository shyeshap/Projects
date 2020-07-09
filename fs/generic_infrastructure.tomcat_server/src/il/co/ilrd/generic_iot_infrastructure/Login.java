package il.co.ilrd.generic_iot_infrastructure;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.stream.Collectors;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

/**
 * Servlet implementation class TomcatServer
 */
@WebServlet("/login")
public class Login extends HttpServlet {
	public int pub; 
	private static final long serialVersionUID = 1L;
	private CompaniesCrud crud;
	private static long ttlMillis = 18_000_000;
	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public Login() {
		super();
		try {
			Class.forName("com.mysql.jdbc.Driver");
			crud = new CompaniesCrud("jdbc:mysql://localhost/GenericIOT", "root", "ct,h kvmkhj");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

	}


	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("application/json");
		PrintWriter out = response.getWriter();
		String jsonStr = null;

		try(BufferedReader reader = request.getReader();){
			jsonStr = reader.lines().collect(Collectors.joining());
		} catch (IOException e) {
			e.printStackTrace();
		}

		JsonObject loginDetails = new JsonParser().parse(jsonStr).getAsJsonObject();
		CompanyDetails comp = crud.read(loginDetails.get("email").getAsString());
		
		System.out.println("created password " + loginDetails.get("password").getAsString());
		System.out.println("expected password " + comp.getPassword());

		if (comp.getEmail() == null || 
				!PasswordEncryptor.validatePassword(loginDetails.get("password").getAsString(), comp.getPassword())) {
			out.println(Status.WRONG_INPUT.toString());
			return;
		} else {
			String token = TokenManager.createJWT(comp.getEmail(), ttlMillis);
			Cookie JWTCookie = new Cookie("token", token);
			JWTCookie.setMaxAge(60*60*60*8);
			response.addCookie(JWTCookie);
			out.println("OK");
			
		}
	}

	/**
	 * @see HttpServlet#doPut(HttpServletRequest, HttpServletResponse)
	 */
	protected void doPut(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		throw new UnsupportedOperationException();
	}

	/**
	 * @see HttpServlet#doDelete(HttpServletRequest, HttpServletResponse)
	 */
	protected void doDelete(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		throw new UnsupportedOperationException();
	}
	
}