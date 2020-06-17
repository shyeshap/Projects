package il.co.ilrd.generic_iot_infrastructure.command;

import com.google.gson.JsonObject;

import il.co.ilrd.generic_iot_infrastructure.Response;

public class PRCommand implements Command {
	
	public PRCommand(JsonObject data) {}
	
	@Override
	public Response execute(JsonObject data) {
		System.out.println("PR");
		
		return new Response(200, "OK");
	}

}
