package il.co.ilrd.generic_iot_infrastructure.msg;

public class Msg {
	private String key;
	private String company;
	private String data;
	
	public Msg(String key, String data, String company) {
		this.key = key;
		this.data = data;
		this.company = company;
	}

	public String getKey() {
		return key;
	}

	public void setKey(String key) {
		this.key = key;
	}

	public String getData() {
		return data;
	}

	public void setData(String data) {
		this.data = data;
	}

	public String getCompany() {
		return company;
	}

	public void setCompany(String company) {
		this.company = company;
	}
}
