package il.co.ilrd.eli;

import com.google.gson.JsonObject;

public class CRCommand implements Command {
	
	JsonObject data;
	
	public CRCommand(JsonObject data) {
		this.data = data;
	}

	@Override
	public Response execute() {
		return new Response(200, "perfect");
	}

}
