package il.co.ilrd.generic_iot_infrastructure.command;

import il.co.ilrd.generic_iot_infrastructure.msg.Data;
import il.co.ilrd.generic_iot_infrastructure.msg.Response;

public interface Command {
	public Response execute(Data data);
}
