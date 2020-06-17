package il.co.ilrd.generic_iot_infrastructure.command;

import com.google.gson.JsonObject;

import il.co.ilrd.generic_iot_infrastructure.Response;

public class IOTCommand implements Command {

	public IOTCommand(JsonObject data) {}
	
	@Override
	public Response execute(JsonObject data) {
		System.out.println("IOT");
		
		return new Response(200, "OK");
	}
	
}
