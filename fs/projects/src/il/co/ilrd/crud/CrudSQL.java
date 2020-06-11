package il.co.ilrd.crud;

import java.sql.*;


public class CrudSQL implements GenericCrud<String, Integer>{
	private Connection con;
	private ResultSet res;
	private int station_id = 1; 
	private boolean flag = true;
	private String table = "file_log";

	CrudSQL(String url, String user, String password){
		try {
			con = DriverManager.getConnection(url, "newuser", "password");
			con.setAutoCommit(false);
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void close() throws Exception {
		flag = false;
		con.close();
		res.close();
	}

	@Override
	public Integer create(String msg) {
		PreparedStatement stmt = null;
		Integer id = null;
		String newMsg = msg.replaceAll("'", "");
		try {
			String sql = "INSERT INTO " +
							table +
							" (station_id, data) VALUES (" + 
							station_id + 
							", '" + 
							newMsg +
							"')";
			stmt = con.prepareStatement(sql);
			stmt.execute();
			sql = "SELECT MAX(id) FROM " + table + " WHERE station_id = " + station_id;
			res = stmt.executeQuery(sql);
			if (res.next() && flag && res != null){
				id = (Integer) res.getInt("MAX(id)");
			}
			con.commit();
		} catch (SQLException e) {
			try {
				con.rollback();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
			System.out.println(newMsg);
			e.printStackTrace();
		}

		return id;
	}

	@Override
	public String read(Integer key) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void update(Integer key, String obj) {
		// TODO Auto-generated method stub

	}

	@Override
	public String delete(Integer key) {
		// TODO Auto-generated method stub
		return null;
	}

}
