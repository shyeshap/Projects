package il.co.ilrd.generic_iot_infrastructure;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import com.google.gson.JsonObject;

public class CompaniesCrud implements IOTCrud {
	private Connection connection;
	
	public CompaniesCrud(String url, String user, String password) {
		System.out.println("crud ctor");
		try {
			connection = DriverManager.getConnection(url, user, password);
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public String create(JsonObject comp_reg) {
		PreparedStatement stmt = null;
	
		try {
			String sql = "INSERT INTO " +
							"Companies" +
							" (company_name, email, password) VALUES ('" + 
							comp_reg.get("company_name").getAsString() + 
							"', '" + 
							comp_reg.get("email").getAsString() +
							"', '" +
							comp_reg.get("password").getAsString() +
							"')";
			System.out.println(sql);
			System.out.println(connection);
			stmt = connection.prepareStatement(sql);
			stmt.execute();
			connection.commit();
		} catch (SQLException e) {
			try {
				connection.rollback();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
			System.out.println("SQLException");
			e.printStackTrace();
		}
		
		return null;
	}

	public JsonObject read(String key) {
		
		return null;
	}

	public void update(String key, JsonObject obj) {
		// TODO Auto-generated method stub
		
	}

	public JsonObject delete(String key) {
		// TODO Auto-generated method stub
		return null;
	}

}
