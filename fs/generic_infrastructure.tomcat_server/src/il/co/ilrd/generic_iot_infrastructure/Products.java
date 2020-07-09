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

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

/**
 * Servlet implementation class Products
 */
@WebServlet("/products")
public class Products extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private ProductsCrud crud;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public Products() {
		super();
		try {
			Class.forName("com.mysql.jdbc.Driver");
			crud = new ProductsCrud("jdbc:mysql://localhost/GenericIOT", "root", "ct,h kvmkhj");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("application/json");
		PrintWriter out = response.getWriter();
		Status status = Status.INVALID_TOKEN;
		JsonObject ret = new JsonObject();
		String email = TokenManager.getEmail(request.getHeader("token"));
		
		if (email != null) {
			JsonArray products = crud.read(email);
			status = Status.OK;
			ret.add("products", products);
		}

		ret.addProperty("status", status.toString());
		out.print(ret);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("application/json");
		PrintWriter out = response.getWriter();
		JsonObject ret = new JsonObject();
		Status status = Status.INVALID_TOKEN;
		String email = TokenManager.getEmail(request.getHeader("token"));
		
		try(BufferedReader reader = request.getReader();){
			String jsonStr = reader.lines().collect(Collectors.joining());
			JsonObject registerDetails = new JsonParser().parse(jsonStr).getAsJsonObject();
			ProductDetails prod = ProductDetails.getProductDetails(registerDetails);
			prod.setEmail(email);
			
			if (prod != null) {
				status = crud.create(prod);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}

		ret.addProperty("status", status.toString());
		out.println(status.toString());
	}

	protected void doPut(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("application/json");
		PrintWriter out = response.getWriter();
		Status status = Status.INVALID_TOKEN;
		String email = TokenManager.getEmail(request.getHeader("token"));
	
		if (email != null) { 
			try(BufferedReader reader = request.getReader();){
				String jsonStr = reader.lines().collect(Collectors.joining());
				JsonObject updateDetails = new JsonParser().parse(jsonStr).getAsJsonObject();
				ProductDetails prod = ProductDetails.getProductDetails(updateDetails);
				prod.setProduct_id(updateDetails.get("product_id").getAsInt());
				status = crud.update(email, prod);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		
		out.println("status: " + status);
	}

	protected void doDelete(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("application/json");
		PrintWriter out = response.getWriter();
		Status status = Status.INVALID_TOKEN;
		String email = TokenManager.getEmail(request.getHeader("token"));
	
		if (email != null) { 
			try(BufferedReader reader = request.getReader();){
				String jsonStr = reader.lines().collect(Collectors.joining());
				JsonObject updateDetails = new JsonParser().parse(jsonStr).getAsJsonObject();
				status = crud.delete(email, updateDetails.get("product_id").getAsInt());
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		out.println(status.toString());
	}
}
