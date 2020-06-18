package il.co.ilrd.generic_iot_infrastructure;

public class HttpGatewayServer {
	String ipAddress;
	int httpPort;
	int threadsNum; 
	
	public HttpGatewayServer(String ipAddress, int httpPort, int threadsNum) {
		this.ipAddress = ipAddress;
		this.httpPort = httpPort;
		this.threadsNum = threadsNum;
	}
	
	private void start() {
		TasksManager tm = new TasksManager(threadsNum);
		new CommandLoader();
		HttpCommunication commun = new HttpCommunication(tm, 4);
		commun.listen(ipAddress, httpPort);
	}
	
	public static void main(String[] args) {
		new HttpGatewayServer("10.1.0.5", 8500, 4).start();
	}

}
