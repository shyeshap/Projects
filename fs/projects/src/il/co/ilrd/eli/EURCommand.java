package il.co.ilrd.eli;

import com.google.gson.JsonObject;

public class EURCommand implements Command {
	
	JsonObject data;
	
	public EURCommand(JsonObject data) {
		this.data = data;
	}
	@Override
	public Response execute() {
		return new Response(501, "There were some problems with the server, sorry :/");
	}

}
