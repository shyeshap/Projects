package il.co.ilrd.generic_iot_infrastructure;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Enumeration;
import java.util.stream.Collectors;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.xml.bind.DatatypeConverter;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;

/**
 * Servlet implementation class Companies
 */
@WebServlet("/companies")
public class Companies extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private CompaniesCrud crud;
	private static String SECRET_KEY = "w0eA2VYklxdRfkLafX7fHBcRdlD8TLYSma6qFJCBBlCRjFLIOHe0N73nJlYuZNR";

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public Companies() {
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
		System.out.println("get");
		response.setContentType("application/json");
		PrintWriter out = response.getWriter();
		String jsonStr = null;
		String token = request.getHeader("token");
		String email = getEmail(token);

		CompanyDetails comp = crud.read(email);

		
		out.println(Status.OK.toString());
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		System.out.println("post");
		response.setContentType("application/json");
		PrintWriter out = response.getWriter();
		String jsonStr = null;

		try(BufferedReader reader = request.getReader();){
			jsonStr = reader.lines().collect(Collectors.joining());
			JsonObject registerDetails = new JsonParser().parse(jsonStr).getAsJsonObject();
			CompanyDetails comp = CompanyDetails.getCompanyDetails(registerDetails);
			if (comp == null) {
				JsonObject ret = new JsonObject();
				ret.addProperty("msg", "one of the fields is missing");
				out.println(ret);
			} else {
				Status status = crud.create(comp);
				out.println(status.toString());
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	protected void doPut(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		System.out.println("put");
		response.setContentType("application/json");
		PrintWriter out = response.getWriter();
		//check token
		try(BufferedReader reader = request.getReader();){
			String jsonStr = reader.lines().collect(Collectors.joining());
			JsonObject updateDetails = new JsonParser().parse(jsonStr).getAsJsonObject();
			CompanyDetails comp = CompanyDetails.getCompanyDetails(updateDetails);
			Status status = crud.update(comp.getEmail(), comp);
			out.println(status.toString());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	protected void doDelete(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		System.out.println("delete");
		response.setContentType("application/json");
		PrintWriter out = response.getWriter();
		//check token
		try(BufferedReader reader = request.getReader();){

			Status status = crud.delete("itai@itai");
			out.println(status.toString());
		} catch (IOException e) {
			e.printStackTrace();
		}
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
		System.out.println("token: " + token);
		return (String)decodeJWT(token).get("email");
	}
}
