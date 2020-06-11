package il.co.ilrd.tests;

import il.co.ilrd.crud.FileMonitor;
import il.co.ilrd.crud.FileObserver;
import il.co.ilrd.crud.FileToSQLObserver;

public class MonitorTest {

	public static void main(String[] args) {
		FileMonitor fm = new FileMonitor("/var/log/syslog");
		try (
			FileObserver fo = new FileObserver("/home/student/Desktop/txt.txt");
			FileToSQLObserver fsql = new FileToSQLObserver("jdbc:mysql://localhost/Observer", "newuser", "password")) {
			//"jdbc:mysql://10.1.0.15/Observer", "root", "ct,h kvmkhj"
			fm.addObserver(fo);
			fm.addObserver(fsql);
			fm.startMonitor();
			Thread.sleep(10000);
			fm.stopMonitor();
			
		} catch (Exception e) {
			e.printStackTrace();
		} 	
	}
}
