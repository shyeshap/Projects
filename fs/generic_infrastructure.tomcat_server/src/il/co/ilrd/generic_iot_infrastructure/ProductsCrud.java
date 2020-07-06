package il.co.ilrd.generic_iot_infrastructure;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.mysql.jdbc.exceptions.MySQLIntegrityConstraintViolationException;

public class ProductsCrud {
	private Connection connection;
	private String table = "Products";
	private String key = "product_id";

	public ProductsCrud(String url, String user, String password) {
		try {
			connection = DriverManager.getConnection(url, user, password);
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	public Status create(ProductDetails prod) {
		System.out.println("create prod");
		PreparedStatement stmt = null;
		try {
			stmt = connection.prepareStatement("INSERT INTO " + table + " (email, model) VALUES (?, ?)");
			stmt.setString(1, prod.getEmail());
			stmt.setString(2, prod.getModel());
			stmt.execute();
		} catch (MySQLIntegrityConstraintViolationException e2) {
			return Status.MODEL_ALREADY_EXIST;
		} catch (SQLException e) {
			try {
				connection.rollback();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
			System.out.println("SQLException");
			e.printStackTrace();
		}

		return Status.OK;
	}

	public JsonArray read(String email) {
		PreparedStatement stmt = null;
		JsonArray productsArray = new JsonArray(); 

		try {
			stmt = connection.prepareStatement("SELECT * FROM " + table + " WHERE email = ?");
			stmt.setString(1, email);
			ResultSet res = stmt.executeQuery();
			productsArray = resultSetToJson(res);
		} catch (MySQLIntegrityConstraintViolationException e2) {
			return null;
		} catch (SQLException e) {
			System.out.println("SQLException");
			e.printStackTrace();
		}

		return productsArray;
	}

	public Status update(String email, ProductDetails prod) {
		PreparedStatement stmt = null;
		Status status = Status.OK;

		try {
			stmt = connection.prepareStatement("UPDATE " + table 
					+ " SET model = ? "
					+ "WHERE " + key + " = '" + prod.getProduct_id() 
					+ "' AND email = '" + email + "'");
			stmt.setString(1, prod.getModel());
			int changedRows = stmt.executeUpdate();
			if (changedRows == 0) {
				status = Status.MODEL_NOT_FOUND;
			}
		} catch (SQLException e) {
			System.out.println("SQLException");
			e.printStackTrace();
		}

		return status; 
	}

	public Status delete(String email, Integer id) {
		PreparedStatement stmt = null;
		Status status = Status.OK;

		try {
			stmt = connection.prepareStatement("DELETE FROM " + table 
					+ " WHERE " + key + " = " + id + " AND email = '" + email + "'");
			int changedRows = stmt.executeUpdate();
			if (changedRows == 0) {
				status = Status.MODEL_NOT_FOUND;
			}
		} catch (SQLException e) {
			System.out.println("SQLException");
			e.printStackTrace();
		}

		return status; 
	}

	private JsonArray resultSetToJson(ResultSet res) throws SQLException {
		JsonArray prodactsArr = new JsonArray();

		while (res.next()) {
			JsonObject product = new JsonObject();
			product.addProperty("product_id", res.getString("product_id"));
			product.addProperty("model", res.getString("model"));
			prodactsArr.add(product);
		}
		return prodactsArr;
	}
}
