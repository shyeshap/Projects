package il.co.ilrd.eli;

import com.google.gson.JsonObject;

public class PRCommand implements Command {
	
	JsonObject data;
	
	public PRCommand(JsonObject data) {
		this.data = data;
	}
	@Override
	public Response execute() {
		return new Response(300, "could be better");
	}

}
