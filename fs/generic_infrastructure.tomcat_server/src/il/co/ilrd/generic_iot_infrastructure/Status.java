package il.co.ilrd.generic_iot_infrastructure;

public enum Status {
	OK 						(200, "OK"),
	WRONG_INPUT				(400, "Wrong input"),
	EMAIL_NOT_FOUND			(400, "Email not found"),
	WRONG_PASSWORD			(400, "Wrong password"),
	EMAIL_ALREADY_IN_USE 	(406, "Email already in use"),
	MODEL_NOT_FOUND			(400, "Model not found"),
	MODEL_ALREADY_EXIST 	(406, "Model already exist");

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
