package il.co.ilrd.generic_iot_infrastructure;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.security.Key;
import java.util.Date;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;

import javax.crypto.spec.SecretKeySpec;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.xml.bind.DatatypeConverter;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import io.jsonwebtoken.JwtBuilder;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;

import java.util.Base64;

/**
 * Servlet implementation class TomcatServer
 */
@WebServlet("/login")
public class Login extends HttpServlet {
	public int pub; 
	private static String SECRET_KEY = "w0eA2VYklxdRfkLafX7fHBcRdlD8TLYSma6qFJCBBlCRjFLIOHe0N73nJlYuZNR";
	private static final long serialVersionUID = 1L;
	private CompaniesCrud crud;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public Login() {
		super();
		System.out.println("comp ctor");
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
		HttpSession session;

		try(BufferedReader reader = request.getReader();){
			jsonStr = reader.lines().collect(Collectors.joining());
		} catch (IOException e) {
			e.printStackTrace();
		}

		JsonObject loginDetails = new JsonParser().parse(jsonStr).getAsJsonObject();
		CompanyDetails comp = crud.read(loginDetails.get("email").getAsString());

		if (comp == null) {
			out.println(Status.EMAIL_NOT_FOUND.toString());
		} else if (!comp.getPassword().equals(loginDetails.get("password").getAsString())) {
			out.println(Status.WRONG_PASSWORD.toString());
		} else {
			String token = createJWT(comp.getEmail());
			Cookie JWTCookie = new Cookie("token", token);
			JWTCookie.setMaxAge(30*60);
			response.addCookie(JWTCookie);
			out.println("OK");
			
		}
	}


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

	private static String createJWT(String email) {
		String s = null;
		try {
			s = Jwts.builder()
					//.setSubject("1234567890")
					//.setId("5c670a74-c8c9-4a21-a000-fd01b65c7773")
					.setIssuedAt(new Date())
					.setExpiration(new Date(System.currentTimeMillis() + TimeUnit.HOURS.toMillis(8)))
					.claim("email", email)
					.signWith(SignatureAlgorithm.HS256, "bigSecret".getBytes("UTF-8"))
					.compact();
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return s;
		
		/*JwtBuilder builder = null;
		//The JWT signature algorithm we will be using to sign the token
		SignatureAlgorithm signatureAlgorithm = SignatureAlgorithm.HS256;
		
		long nowMillis = System.currentTimeMillis();
		Date now = new Date(nowMillis);
		
		//We will sign our JWT with our ApiKey secret
		
		byte[] apiKeySecretBytes = DatatypeConverter.parseBase64Binary(SECRET_KEY);
		Key signingKey = new SecretKeySpec(apiKeySecretBytes, signatureAlgorithm.getJcaName());
		
		builder = Jwts.builder()
				.setIssuedAt(now)
				.setSubject(comp.getEmail())
				.signWith(signatureAlgorithm, signingKey);
		
		//if it has been specified, let's add the expiration
		if (ttlMillis > 0) {
			long expMillis = nowMillis + ttlMillis;
			Date exp = new Date(expMillis);
			builder.setExpiration(exp);
		}
		String compactJWT = builder.compact();
		//Let's set the JWT Claims
		return compactJWT;*/
	}

	
}