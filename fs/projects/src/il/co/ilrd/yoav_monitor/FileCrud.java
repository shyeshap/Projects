package il.co.ilrd.yoav_monitor;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class FileCrud implements GenericCrud<String, Integer> {
	BufferedWriter write = null;
	//String filePath = null;
	Integer lineNum = 0;
	
	public FileCrud(String filePath) {
		//this.filePath = filePath;
		try {
			write = new BufferedWriter(new FileWriter(filePath));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public void close() throws Exception {
		write.close();
	}
	
	@Override
	public Integer create(String obj) {		
		try {
			write.write(obj + "\n");
			write.flush();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return (lineNum++);
	}
	
	@Override
	public String read(Integer key) {
		throw new UnsupportedOperationException();
	}
	
	@Override
	public void update(Integer key, String obj) {
		throw new UnsupportedOperationException();
	}
	
	@Override
	public String delete(Integer key) {
		throw new UnsupportedOperationException();
	}
}