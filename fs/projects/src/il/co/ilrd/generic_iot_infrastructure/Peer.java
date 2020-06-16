package il.co.ilrd.generic_iot_infrastructure;

import il.co.ilrd.generic_iot_infrastructure.msg.Response;

public interface Peer {
	void send(Response response);
}
