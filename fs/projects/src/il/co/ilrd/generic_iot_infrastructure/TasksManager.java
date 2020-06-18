package il.co.ilrd.generic_iot_infrastructure;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import com.google.gson.JsonObject;

public class TasksManager {
	private ExecutorService tp;
	
	public TasksManager(int threadsNum) {
		System.out.println("task maneger ctor");
		tp = Executors.newFixedThreadPool(threadsNum);
	}
	
	public void createAndSubmitTask(JsonObject json, Peer peer) {
		System.out.println("create and handle task");
		Task task = createTask(json, peer);
		tp.submit(task);
	}
	
	private Task createTask(JsonObject requestBody, Peer peer) {
		System.out.println("create task");
		String key = requestBody.get("key").getAsString();
		JsonObject data = requestBody.get("data").getAsJsonObject();
		return new Task(key, data, peer);
	}
}
