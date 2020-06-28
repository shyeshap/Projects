package il.co.ilrd.generic_iot_infrastructure;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Map.Entry;
import java.sql.ResultSetMetaData;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.mysql.jdbc.exceptions.MySQLIntegrityConstraintViolationException;

public class CompaniesCrud implements IOTCrud {
	private Connection connection;

	public CompaniesCrud(String url, String user, String password) {
		try {
			connection = DriverManager.getConnection(url, user, password);
			connection.setAutoCommit(false);
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	public JsonObject create(JsonObject comp_reg) {
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
			stmt = connection.prepareStatement(sql);
			stmt.execute();
			connection.commit();
		} catch (MySQLIntegrityConstraintViolationException e2) {

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
		System.out.println("read");
		PreparedStatement stmt = null;
		JsonObject jRecord = null;

		try {
			String sql = "SELECT * FROM Companies WHERE email = '" + key + "'";
			stmt = connection.prepareStatement(sql);
			System.out.println(stmt.toString());
			ResultSet rs = stmt.executeQuery();
			connection.commit();
			jRecord = new JsonObject();
			ResultSetMetaData meta = rs.getMetaData();
			if (rs.next()) {
				int columns = meta.getColumnCount();
				for (int i = 1; i <= columns; ++i ) {
					jRecord.addProperty(meta.getColumnName(i), rs.getObject(i).toString());
				}
			}
		} catch (MySQLIntegrityConstraintViolationException e2) {
			System.out.println("exception");
		} catch (SQLException e) {
			try {
				connection.rollback();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
			System.out.println("SQLException");
			e.printStackTrace();
		}

		return jRecord;
	}

	public void update(String key, JsonObject obj) {
		PreparedStatement stmt = null;

			try {
				stmt = connection.prepareStatement("UPDATE items SET company_name = ? WHERE email = '" + key.replace("\"", "") + "'");
				for (Entry<String, JsonElement> e : obj.entrySet()) {
					System.out.println(e.getKey());
					System.out.println(e.getValue().toString().replace("\"", ""));
					//stmt.setString(1, "company_name");
					stmt.setString(2, e.getValue().toString().replace("\"", ""));
					System.out.println(stmt.toString());
					stmt.execute();
				}
				connection.commit();
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
	}

	public JsonObject delete(JsonObject key) {
		// TODO Auto-generated method stub
		return null;
	}

}
