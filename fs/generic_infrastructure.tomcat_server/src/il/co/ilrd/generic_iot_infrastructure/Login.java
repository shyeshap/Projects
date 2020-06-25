package il.co.ilrd.generic_iot_infrastructure;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.security.Key;
import java.util.Date;
import java.util.stream.Collectors;

import javax.crypto.spec.SecretKeySpec;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.xml.bind.DatatypeConverter;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import io.jsonwebtoken.*;

/**
 * Servlet implementation class TomcatServer
 */
@WebServlet("/login")
public class Login extends HttpServlet {
	public int pub; 
	private static String SECRET_KEY;
	private static final long serialVersionUID = 1L;
	private CompaniesCrud crud = new CompaniesCrud("jdbc:mysql://localhost/GenericIOT", "newuser", "password");;
	
	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public Login() {
		super();
		
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("application/json");
		PrintWriter out = response.getWriter();
		//createJWT(request.getParameter("id"), request.getParameter("password"), request.getParameter("id"));
		/*
		out.println("<HTML>");
		out.println("<HEAD> <TITLE> LoginPage </TITLE> <HEAD>");
		out.println("<BODY>");
		if (values != null) {
			out.println("<H4> Hello " + values[0] +  "</H4>");
		} else {
			out.println("<H4> Hello World </H4>");
		}
		out.println("</BODY> </HTML>");*/
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
		
		JsonObject record = crud.read(loginDetails.get("email").getAsString());
		
		if (record.get("password").getAsString() != loginDetails.get("password").getAsString()) {
			
		} else {
			createJWT(record.get("company_name").getAsString(), record.get("password").getAsString(), 1_800_000);
			response.setCharacterEncoding("UTF-8");
			out.print(record);
			out.flush();
		}
	}
	/*
				if(DBCrud.read().equals(user) && password.equals(pwd)){
					Cookie loginCookie = new Cookie("user",user);
					//setting cookie to expiry in 30 mins
					loginCookie.setMaxAge(30*60);
					response.addCookie(loginCookie);
					response.sendRedirect("LoginSuccess.jsp");
				}else{
					RequestDispatcher rd = getServletContext().getRequestDispatcher("/login.html");
					PrintWriter out= response.getWriter();
					out.println("<font color=red>Either user name or password is wrong.</font>");
					rd.include(request, response);
				}*/



/**
 * @see HttpServlet#doPut(HttpServletRequest, HttpServletResponse)
 */
protected void doPut(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
	// TODO Auto-generated method stub
}

/**
 * @see HttpServlet#doDelete(HttpServletRequest, HttpServletResponse)
 */
protected void doDelete(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
	// TODO Auto-generated method stub
}

private static String createJWT(String id, String password, long ttlMillis) {

	//The JWT signature algorithm we will be using to sign the token
	SignatureAlgorithm signatureAlgorithm = SignatureAlgorithm.HS256;

	long nowMillis = System.currentTimeMillis();
	Date now = new Date(nowMillis);

	//We will sign our JWT with our ApiKey secret
	byte[] apiKeySecretBytes = DatatypeConverter.parseBase64Binary(SECRET_KEY);
	Key signingKey = new SecretKeySpec(apiKeySecretBytes, signatureAlgorithm.getJcaName());

	//Let's set the JWT Claims
	JwtBuilder builder = Jwts.builder().setId(id)
			.setIssuedAt(now)
			.setSubject(password)
			.signWith(signingKey);

	//if it has been specified, let's add the expiration
	if (ttlMillis > 0) {
		long expMillis = nowMillis + ttlMillis;
		Date exp = new Date(expMillis);
		builder.setExpiration(exp);
	}  

	System.out.println(builder.toString());
	//Builds the JWT and serializes it to a compact, URL-safe string
	return builder.compact();
}

private static Claims decodeJWT(String jwt) {
	//This line will throw an exception if it is not a signed JWS (as expected)
	Claims claims = Jwts.parser()
			.setSigningKey(DatatypeConverter.parseBase64Binary(SECRET_KEY))
			.parseClaimsJws(jwt).getBody();
	return claims;
}
}