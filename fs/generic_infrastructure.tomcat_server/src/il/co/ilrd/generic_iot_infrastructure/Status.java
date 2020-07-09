package il.co.ilrd.generic_iot_infrastructure;

public enum Status {
	OK 						(200, "OK"),
	WRONG_INPUT				(400, "Wrong input"),
	EMAIL_ALREADY_IN_USE 	(406, "Email already in use"),
	INVALID_TOKEN			(400, "Invalid token"),
	MODEL_NOT_FOUND			(405, "Model not found");


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
