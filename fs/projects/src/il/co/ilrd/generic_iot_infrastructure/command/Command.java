package il.co.ilrd.generic_iot_infrastructure.command;

import com.google.gson.JsonObject;

import il.co.ilrd.generic_iot_infrastructure.Response;

public interface Command {
	public Response execute(JsonObject data);
}
