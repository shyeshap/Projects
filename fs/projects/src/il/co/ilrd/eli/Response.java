package il.co.ilrd.eli;

public class Response {
	private int statusCode;
	private String msg;

	public Response(int statusCode, String msg) {
		this.statusCode = statusCode;
		this.msg = msg;
	}

	public int getStatusCode() {
		return statusCode;
	}

	public String getMsg() {
		return msg;
	}
}
