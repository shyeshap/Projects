package il.co.ilrd.eli;

import java.io.IOException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class GatewayServer {
	private String ipAddress;
	private ExecutorService threadPool;
	private TaskManagement taskManagement;
	
	public GatewayServer(String ipAddress) {
		this.ipAddress = ipAddress;
		threadPool = Executors.newFixedThreadPool(4);
		taskManagement = new TaskManagement(threadPool);
		new HttpCommunication(taskManagement).listen(ipAddress, 8500);
		//new TcpCommunication().listen(ipAddress, 8866);
		//new UdpCommunication().listen(ipAddress, 6868);
	}
	
	public static void main(String[] args) throws IOException {
		GatewayServer server = new GatewayServer("10.1.0.48");
		
	}
}
