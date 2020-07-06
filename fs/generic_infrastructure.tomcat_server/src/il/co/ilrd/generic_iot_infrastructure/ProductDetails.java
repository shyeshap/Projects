package il.co.ilrd.generic_iot_infrastructure;

import java.sql.ResultSet;
import java.sql.SQLException;

import com.google.gson.JsonObject;

public class ProductDetails {
	String email;
	String model;
	Integer product_id;
	

	public ProductDetails() {}

	public static ProductDetails getProductDetails(ResultSet productDetails) {
		ProductDetails prod = new ProductDetails();

		try {
			if (productDetails.next()) {
				prod.email = productDetails.getString("email");
				prod.model = productDetails.getString("model");
				prod.model = productDetails.getString("product_id");
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return prod;
	}
	
	public static ProductDetails getProductDetails(JsonObject productDetails) {
		ProductDetails prod = new ProductDetails();
		
		prod.model = productDetails.get("model").getAsString();

		return prod;
	} 
	
	public Integer getProduct_id() {
		return product_id;
	}
	
	public void setProduct_id(Integer product_id) {
		this.product_id = product_id;
	}

	public String getModel() {
		return model;
	}
	public void setModel(String model) {
		this.model = model;
	}
	
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
}
