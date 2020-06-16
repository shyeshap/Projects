package il.co.ilrd.generic_iot_infrastructure.command;

import il.co.ilrd.generic_iot_infrastructure.msg.Data;
import il.co.ilrd.generic_iot_infrastructure.msg.Response;

public class CRCommand implements Command {
	
	public CRCommand(Data data) {
	}
	
	@Override
	public Response execute(Data data) {
		return new Response(200, "OK");
	}

}
