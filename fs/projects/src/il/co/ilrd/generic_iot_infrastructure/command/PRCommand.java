package il.co.ilrd.generic_iot_infrastructure.command;

import com.google.gson.JsonObject;

import il.co.ilrd.generic_iot_infrastructure.Response;

public class PRCommand implements Command {
	JsonObject data;
	
	public PRCommand(JsonObject data) {
		this.data = data;
	}

	@Override
	public Response execute() {
		System.out.println("PR");
		return new Response(200, "OK");
	}

}
