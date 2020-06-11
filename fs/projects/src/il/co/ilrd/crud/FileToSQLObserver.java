package il.co.ilrd.crud;

import java.io.IOException;
import java.util.Observable;
import java.util.Observer;

public class FileToSQLObserver implements AutoCloseable, Observer {
	private CrudSQL SQLCrud;

	public FileToSQLObserver(String url, String user, String password) throws IOException {
		SQLCrud = new CrudSQL(url, user, password);
	}
	
	@Override
	public void update(Observable monitor, Object line) {
		SQLCrud.create((String)line);
	}
	
	@Override
	public void close() throws Exception {
		SQLCrud.close();
	}
}
