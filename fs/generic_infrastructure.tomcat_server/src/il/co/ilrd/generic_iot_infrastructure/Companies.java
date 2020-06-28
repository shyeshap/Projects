package il.co.ilrd.generic_iot_infrastructure;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;
import java.util.Map.Entry;
import java.util.Set;
import java.util.stream.Collectors;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.websocket.Session;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.mysql.jdbc.exceptions.MySQLIntegrityConstraintViolationException;

/**
 * Servlet implementation class Companies
 */
@WebServlet("/companies")
public class Companies extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private CompaniesCrud crud;
	
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Companies() {
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
		System.out.println("get");
		response.setContentType("application/json");
		PrintWriter out = response.getWriter();
		/*
		String jsonStr = null;
		try(BufferedReader reader = request.getReader();) {
			jsonStr = reader.lines().collect(Collectors.joining());
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		JsonObject registerDetails = new JsonParser().parse(jsonStr).getAsJsonObject();
		*/
		JsonObject record = crud.read((String)request.getSession(false).getAttribute("company_id"));
		
		
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
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		JsonObject registerDetails = new JsonParser().parse(jsonStr).getAsJsonObject();
		
		JsonObject record = crud.read((String)request.getSession().getAttribute("company_id"));
		
		if (record.size() == 0) {
			out.print(crud.create(registerDetails));
		} else {
			System.out.println("user already exist");
		}
	 	/*
	 	for (Entry<String, JsonElement> e : record.entrySet()) {
			session.setAttribute(e.getKey(), e.getValue());
			
		}
		*/
		
	}
	protected void doPut(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		System.out.println("put");
		response.setContentType("application/json");
		PrintWriter out = response.getWriter();
		
		String jsonStr = null;
		try(BufferedReader reader = request.getReader();){
			jsonStr = reader.lines().collect(Collectors.joining());
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		
		String email = request.getSession(false).getAttribute("email").toString();
		JsonObject updateDetails = new JsonParser().parse(jsonStr).getAsJsonObject();
		crud.update(email, updateDetails);
		
	}
}
