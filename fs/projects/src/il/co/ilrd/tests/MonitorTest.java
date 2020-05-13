package il.co.ilrd.tests;

import il.co.ilrd.crud.FileMonitor;
import il.co.ilrd.crud.FileObserver;

public class MonitorTest {

	public static void main(String[] args) {
		FileMonitor fm = new FileMonitor("/var/log/syslog");
		try (FileObserver fo = new FileObserver("/home/ol81-21/Desktop/txt.txt")) {
			fm.addObserver(fo);
			fm.startMonitor();
			Thread.sleep(10000);
			fm.stopMonitor();
			fo.close();
		} catch (Exception e) {
			e.printStackTrace();
		} 		
	}
}
