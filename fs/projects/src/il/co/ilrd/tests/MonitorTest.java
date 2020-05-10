package il.co.ilrd.tests;

import il.co.ilrd.crud.FileMonitor;
import il.co.ilrd.crud.FileObserver;

public class MonitorTest {

	public static void main(String[] args) {
		FileMonitor fm = new FileMonitor("/var/log/syslog");
		fm.addObserver(new FileObserver("/home/ol81-21/Desktop/txt.txt"));
		fm.startMonitor();
		try {
			Thread.sleep(50000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		fm.stopMonitor();
	}
}
