package il.co.ilrd.generic_iot_infrastructure;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.stream.Collectors;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

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
			System.out.println("here");
			crud = new CompaniesCrud("jdbc:mysql://localhost/GenericIOT", "root", "ct,h kvmkhj");
			System.out.println(crud);
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
		System.out.println("post");
		response.setContentType("application/json");
		PrintWriter out = response.getWriter();
		
		String jsonStr = null;
		try(BufferedReader reader = request.getReader();){
			jsonStr = reader.lines().collect(Collectors.joining());
			System.out.println(jsonStr);
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		JsonObject registerDetails = new JsonParser().parse(jsonStr).getAsJsonObject();
		
		String record = crud.create(registerDetails);
		
		System.out.println(record);
	}

}
