package il.co.ilrd.generic_iot_infrastructure.command;

import com.google.gson.JsonObject;

import il.co.ilrd.generic_iot_infrastructure.Response;

public class CRCommand implements Command {
	private JsonObject data;
	
	public CRCommand(JsonObject data) {
		this.data = data;
	}
	
	@Override
	public Response execute() {
		System.out.println("CR");
		return new Response(200, "OK");
	}
}
