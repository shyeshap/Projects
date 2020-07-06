package il.co.ilrd.generic_iot_infrastructure;

import java.sql.ResultSet;
import java.sql.SQLException;

import com.google.gson.JsonObject;

public class CompanyDetails {
	private int company_id;
	private String email;
	private String company_name;
	private char[] password;
	private char[] salt;

	private CompanyDetails() {}

	public static CompanyDetails getCompanyDetails(ResultSet companyDetails) {
		CompanyDetails comp = new CompanyDetails();

		try {
			if (companyDetails.next()) {
				comp.company_id = companyDetails.getInt("company_id");
				comp.company_name = companyDetails.getString("company_name");
				comp.email = companyDetails.getString("email");
				comp.password = companyDetails.getString("password").toCharArray();
				comp.salt = companyDetails.getString("salt").toCharArray();
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
		comp.password = PasswordEncryptor.hash(companyDetails.get("password").getAsString().toCharArray(), PasswordEncryptor.getNextSalt());

		return comp;
	}

	public char[] getSalt() {
		return salt;
	}

	public void setSalt(char[] salt) {
		this.salt = salt;
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

	public char[] getPassword() {
		return password;
	}

	public void setPassword(char[] password) {
		this.password = password;
	}

	public JsonObject toJson() {
		JsonObject companyJson = new JsonObject();
		companyJson.addProperty("company_id", company_id);
		companyJson.addProperty("email", email);
		companyJson.addProperty("company_name", company_name);
		return companyJson;
	}
}
