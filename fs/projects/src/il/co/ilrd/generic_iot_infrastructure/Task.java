package il.co.ilrd.generic_iot_infrastructure;

import com.google.gson.JsonObject;

import il.co.ilrd.generic_iot_infrastructure.command.Command;

public class Task implements Runnable {
	String key;
	JsonObject data;
	private Peer peer;
	
	public Task(String key, JsonObject data, Peer peer) {
		this.key = key;
		this.data = data;
		this.peer = peer;
	}

	public String getKey() {
		return key;
	}

	public JsonObject getData() {
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
