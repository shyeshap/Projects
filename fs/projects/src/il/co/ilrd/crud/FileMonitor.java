package il.co.ilrd.crud;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.ClosedWatchServiceException;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;
import java.util.Observable;


public class FileMonitor extends Observable {

	private String file;
    private volatile boolean keepMonitoring = true;
    private Thread t;
    private WatchService watchService;
    
    public <T> FileMonitor(String fileToMonitor){
    	file =fileToMonitor;
    }
    
    public void copyFile(BufferedReader reader) throws IOException {
    	String line = null;
    	while ((line = reader.readLine()) != null ) {
    		setChanged();
    		notifyObservers(line);  
    	}
    }
    
    public void startMonitor() {
        t = new Thread(() -> {
        	try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
        		watchService = FileSystems.getDefault().newWatchService();
        		Path dirPath = Paths.get(new File(file).getParent());
        		dirPath.register(watchService, StandardWatchEventKinds.ENTRY_MODIFY);
        		copyFile(reader);
        		WatchKey key;
        		String line;
        		while (keepMonitoring) {
        			while ((line = reader.readLine()) != null) {
        				setChanged();
        				notifyObservers(line);          
        			}
        			key = watchService.take();
        			key.pollEvents();
        			if (!key.reset()) { break; }
        		}
        	} catch (IOException e) {
        		e.printStackTrace();    
        	}catch (InterruptedException e) {

        	} catch (ClosedWatchServiceException e) {
        		System.err.println("Monitor Closed");
        	}

        });
        
        t.start();
    }

    public void stopMonitor() {
    	try {
			watchService.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
    	keepMonitoring = false;
    }


}