package il.co.ilrd.eli;

import com.google.gson.JsonObject;

public class IOTCommand implements Command {
	
	JsonObject data;
	
	public IOTCommand(JsonObject data) {
		this.data = data;
	}
	@Override
	public Response execute() {
		return new Response(404, "Not Found");
	}

}
