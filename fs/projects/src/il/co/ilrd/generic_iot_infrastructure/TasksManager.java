package il.co.ilrd.generic_iot_infrastructure;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import il.co.ilrd.generic_iot_infrastructure.msg.Msg;
import il.co.ilrd.generic_iot_infrastructure.msg.Task;

public class TasksManager {
	private ExecutorService tp;
	
	public TasksManager() {
		tp = Executors.newFixedThreadPool(4);
	}
	
	public void createAndSubmitTask(Msg msg, Peer peer) {
		Task task = createTask(msg, peer);
		tp.submit(task, peer);
	}
	
	private Task createTask(Msg msg, Peer peer) {
		return new Task(msg, peer);
	}
}
