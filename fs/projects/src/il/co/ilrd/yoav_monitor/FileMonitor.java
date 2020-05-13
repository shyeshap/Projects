package il.co.ilrd.yoav_monitor;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;
import java.util.Observable;

public class FileMonitor extends Observable {
	
	private File monitoredFile = null;
	private volatile boolean run_flag = true;
	
	public FileMonitor(String monitoredFilePath) {
		monitoredFile = new File(monitoredFilePath);
	}
	
	private void copyPreModify(BufferedReader reader) {
		String line = null;
		try {
			while ((line = reader.readLine()) != null) {
				setChanged();
				notifyObservers(line);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	public void start() {
		(new Thread(new Runnable() {
			@Override
			public void run() {
				try (BufferedReader reader = new BufferedReader(new FileReader(monitoredFile));
						WatchService watcher = FileSystems.getDefault().newWatchService();) {
					
					Path dir = Paths.get(monitoredFile.getParent());
					dir.register(watcher, StandardWatchEventKinds.ENTRY_MODIFY);
					copyPreModify(reader);
	                while (run_flag) {
	                    WatchKey key = watcher.take();
	                    key.pollEvents();
	                    if (run_flag) {
	                    	setChanged();
	                    	notifyObservers(reader.readLine());
	                    }
	                    if (!key.reset()) { break; }
	                }
				} catch (IOException e) {
					e.printStackTrace();
				} catch (InterruptedException e) {
					e.printStackTrace();
				} 
			}
			})).start();
	}
	
	public void stop() {
		run_flag = false;
	}
}
