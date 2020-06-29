package il.co.ilrd.generic_iot_infrastructure;

import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;

import com.google.gson.JsonObject;

public class CompanyDetails {
	private int company_id;
	private String email;
	private String company_name;
	private String password;

	public CompanyDetails() {}

	public static CompanyDetails getCompanyDetails(ResultSet companyDetails) {
		CompanyDetails comp = new CompanyDetails();

		try {
			if (companyDetails.next()) {
				comp.company_id = companyDetails.getInt("company_id");
				comp.company_name = companyDetails.getString("company_name");
				comp.email = companyDetails.getString("email");
				comp.password = companyDetails.getString("password");
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return comp;
	}
	public static CompanyDetails getCompanyDetails(JsonObject companyDetails) {
		CompanyDetails comp = new CompanyDetails();

		comp.company_name = companyDetails.get("company_name").getAsString();
		comp.email = companyDetails.get("email").getAsString();
		comp.password = companyDetails.get("password").getAsString();

		if (comp.company_name == null || comp.email == null || comp.password == null) {
			return null;
		}

		return comp;
	}

	public int getId() {
		return company_id;
	}

	public void setId(int id) {
		this.company_id = id;
	}

	public String getEmail() {
		return email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public String getCompanyName() {
		return company_name;
	}

	public void setCompanyName(String company_name) {
		this.company_name = company_name;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}
}
