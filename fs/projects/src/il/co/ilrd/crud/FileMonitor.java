package il.co.ilrd.crud;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Observable;

public class FileMonitor extends Observable {

    private String path;
    private volatile boolean keepMonitoring = true;

    public <T> FileMonitor(String fileToMonitor){
    	setChanged();
        notifyObservers(null);
    	path = fileToMonitor;
    }
    
    public void startMonitor() {
        Thread t = new Thread(() -> { 
            String line = null;
            try (BufferedReader reader = new BufferedReader(new FileReader(path))){
                while (keepMonitoring) {
                    if ((line = reader.readLine()) != null ) {
                        setChanged();
                        notifyObservers(line);
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
        t.start();
    }

    public void stopMonitor() {
        keepMonitoring = false;
    }
}