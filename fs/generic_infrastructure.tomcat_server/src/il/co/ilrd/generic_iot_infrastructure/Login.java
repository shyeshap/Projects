package il.co.ilrd.generic_iot_infrastructure;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.Date;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.JwtBuilder;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;

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

		if (comp.getEmail() == null) {
			out.println(Status.EMAIL_NOT_FOUND.toString());
		} else if (!PasswordEncryptor.validatePassword(loginDetails.get("password").getAsString(), comp.getPassword())) {
			out.println(Status.WRONG_PASSWORD.toString());
			return;
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
		throw new UnsupportedOperationException();
	}

	/**
	 * @see HttpServlet#doDelete(HttpServletRequest, HttpServletResponse)
	 */
	protected void doDelete(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		throw new UnsupportedOperationException();
	}

	private static String createJWT(String email) {
		long nowMillis = System.currentTimeMillis();
		Date now = new Date(nowMillis);
		JwtBuilder builder = null;
		
		try {
			builder = Jwts.builder()
					.setIssuedAt(now)
					.setExpiration(new Date(System.currentTimeMillis() + TimeUnit.HOURS.toMillis(8)))
					.claim("email", email)
					.signWith(SignatureAlgorithm.HS256, "bigSecret".getBytes("UTF-8"));
			if (ttlMillis > 0) {
				long expMillis = nowMillis + ttlMillis;
				Date exp = new Date(expMillis);
				builder.setExpiration(exp);
			}
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		
		return builder.compact();
	}
	
	private static Claims decodeJWT(String token) {
		Claims claims;
        try {
            claims = Jwts.parser()
            		.setSigningKey("bigSecret".getBytes("UTF-8"))
        			.parseClaimsJws(token)
                    .getBody();
        } catch (Exception e) {
            claims = null;
        }
        
        return claims;
	}
	
	public static String getEmail(String token) {
		String email = null;
		Claims claims = decodeJWT(token);
		
		if (claims != null) {
			email = (String)claims.get("email");
		}
		return email;
	}
	
}