package il.co.ilrd.generic_iot_infrastructure;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.mysql.jdbc.exceptions.MySQLIntegrityConstraintViolationException;

public class CompaniesCrud {
	private Connection connection;
	private String table = "Companies";
	private String key = "email";

	public CompaniesCrud(String url, String user, String password) {
		try {
			connection = DriverManager.getConnection(url, user, password);
			connection.setAutoCommit(false);
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	public Status create(CompanyDetails comp) {
		PreparedStatement stmt = null;
		try {
			stmt = connection.prepareStatement("INSERT INTO " + table + " (company_name, email, encrypted_password) VALUES (?, ?, ?)");
			stmt.setString(1, comp.getCompanyName());
			stmt.setString(2, comp.getEmail());
			stmt.setString(3, comp.getPassword());
			stmt.execute();
			connection.commit();
		} catch (MySQLIntegrityConstraintViolationException e2) {
			return Status.EMAIL_ALREADY_IN_USE;
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

	public CompanyDetails read(String email) {
		PreparedStatement stmt = null;
		CompanyDetails comp = null;

		try {
			stmt = connection.prepareStatement("SELECT * FROM " + table + " WHERE " + key + " = ?");
			stmt.setString(1, email);
			ResultSet rs = stmt.executeQuery();
			connection.commit();
			comp = CompanyDetails.getCompanyDetails(rs);

		} catch (MySQLIntegrityConstraintViolationException e2) {
			return null;
		} catch (SQLException e) {
			try {
				connection.rollback();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
			System.out.println("SQLException");
			e.printStackTrace();
		}

		return comp;
	}

	public Status update(String email, CompanyDetails comp) {
		PreparedStatement stmt = null;
		Status status = Status.OK;

		try {
			stmt = connection.prepareStatement("UPDATE " + table + " SET company_name = ? WHERE " + key + " = '" + email + "'");
			stmt.setString(1, comp.getCompanyName());
			int changedRows = stmt.executeUpdate();
			connection.commit();
			if (changedRows == 0) {
				status = Status.INVALID_TOKEN;
			}
		} catch (SQLException e1) {

			e1.printStackTrace();
		}

		return status; 
	}
//FIXME delete all products of company
	public Status delete(String email) {
		PreparedStatement stmt = null;
		Status status = Status.OK;

		try {
			stmt = connection.prepareStatement("DELETE FROM Companies WHERE " + key + " = '" + email + "'");
			int changedRows = stmt.executeUpdate();
			connection.commit();
			if (changedRows == 0) {
				status = Status.INVALID_TOKEN;
			}
		} catch (SQLException e1) {
			e1.printStackTrace();
		}

		return status; 
	}

}

