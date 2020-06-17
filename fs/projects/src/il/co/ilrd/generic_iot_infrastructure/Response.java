package il.co.ilrd.generic_iot_infrastructure;

public class Response {
	private int statusCode;
	private String statusMsg;
	
	public Response (int statusCode, String statusMsg) {
		this.statusCode = statusCode;
		this.statusMsg = statusMsg;
	}
	
	public String ToString() {
		return "HTTP/1.1 " + statusCode + " " + statusMsg;
	}

	public int getStatusCode() {
		return statusCode;
	}

	public void setStatusCode(int statusCode) {
		this.statusCode = statusCode;
	}

	public String getStatusMsg() {
		return statusMsg;
	}

	public void setStatusMsg(String statusMsg) {
		this.statusMsg = statusMsg;
	}
}
