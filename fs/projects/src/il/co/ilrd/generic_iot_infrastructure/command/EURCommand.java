package il.co.ilrd.generic_iot_infrastructure.command;

import com.google.gson.JsonObject;

import il.co.ilrd.generic_iot_infrastructure.Response;

public class EURCommand implements Command {
	JsonObject data;
	public EURCommand(JsonObject data) {
		this.data = data;
	}
	
	@Override
	public Response execute() {
		System.out.println("EUR");
		return new Response(200, "OK");
	}

}
