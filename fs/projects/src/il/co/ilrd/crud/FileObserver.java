package il.co.ilrd.crud;

import java.io.IOException;
import java.util.Observable;
import java.util.Observer;

public class FileObserver implements AutoCloseable, Observer {
	private CrudFile crud;
	
	public FileObserver(String filePath) throws IOException {
		this.crud = new CrudFile(filePath);
	}

	@Override
	public void update(Observable monitor, Object line) {
		crud.create((String)line);
	}
	
	@Override
	public void close() throws Exception {
		crud.close();
	}
}
