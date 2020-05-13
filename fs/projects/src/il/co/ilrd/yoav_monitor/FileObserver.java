package il.co.ilrd.yoav_monitor;

import java.util.Observable;
import java.util.Observer;

public class FileObserver implements Observer{

	GenericCrud<String, Integer> crud;

	public FileObserver(String filePath) {
		crud = new FileCrud(filePath);
	}

	@Override
	public void update(Observable o, Object line) {
		crud.create((String)line);
	}
	public void close() {
		try {
			crud.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
