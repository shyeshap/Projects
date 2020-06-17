package il.co.ilrd.generic_iot_infrastructure;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import com.google.gson.JsonObject;

public class TasksManager {
	private ExecutorService tp;
	
	public TasksManager() {
		tp = Executors.newFixedThreadPool(4);
	}
	
	public void createAndSubmitTask(JsonObject json, Peer peer) {
		Task task = createTask(json, peer);
		tp.submit(task);
	}
	
	private Task createTask(JsonObject requestBody, Peer peer) {
		String key = requestBody.get("key").getAsString();
		JsonObject data = requestBody.get("data").getAsJsonObject();
		return new Task(key, data, peer);
	}
}
