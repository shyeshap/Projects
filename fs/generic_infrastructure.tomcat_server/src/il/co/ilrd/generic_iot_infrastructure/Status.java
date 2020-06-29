package il.co.ilrd.generic_iot_infrastructure;

public enum Status {
	OK 						(200, "OK"),
	EMAIL_NOT_FOUND			(400, "Email not found"),
	WRONG_PASSWORD			(400, "Wrong password"),
	EMAIL_ALREADY_IN_USE 	(406, "Email already in use");

	int code;
	String description;

	Status(int code, String description) { }

	public int getCode() {
		return code;
	}

	public String getDescription() {
		return description;
	}
}
