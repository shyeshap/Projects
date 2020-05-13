package il.co.ilrd.crud;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

class CrudFile implements GenericCrud<String, Integer> {
	
	private Integer noOfLines = 0;
	private BufferedWriter writer;
	
	CrudFile(String outputFilePath) {
		try {
			writer = new BufferedWriter(new FileWriter(outputFilePath, true));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public void close() throws Exception {
		writer.close();
	}

	@Override
	public Integer create(String line) {
		try {
			writer.append(line);
			writer.newLine();
			writer.flush();
			++noOfLines;
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return noOfLines;
	}

	@Override
	public String read(Integer key) {
		throw (new UnsupportedOperationException());
	}

	@Override
	public void update(Integer key, String obj) {
		throw (new UnsupportedOperationException());
	}

	@Override
	public String delete(Integer key) {
		throw (new UnsupportedOperationException());
	}

}
