package il.co.ilrd.generic_iot_infrastructure.msg;

import il.co.ilrd.design_patterns.Factory;
import il.co.ilrd.generic_iot_infrastructure.Peer;
import il.co.ilrd.generic_iot_infrastructure.SingletonCommandFactory;
import il.co.ilrd.generic_iot_infrastructure.command.Command;

public class Task implements Runnable {
	String key;
	Data data;
	private Factory<String, Command, Data> factory;
	private Peer peer;
	
	public Task(Msg msg, Peer peer) {
		key = msg.getKey();
		data = new Data(msg.getData(), msg.getCompany());
		this.peer = peer;
	}

	public String getKey() {
		return key;
	}

	public Data getData() {
		return data;
	}

	@Override
	public void run() {
		Command commmand = SingletonCommandFactory.getInstance().create(key, data);
		Response response = commmand.execute(data);
		System.out.println("peer" + peer);
		peer.send(response);
	}

}
