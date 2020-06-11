package il.co.ilrd.JDBCEx;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class IsolationLevel {
	public static void main(String args[]) throws SQLException {
		String url = "jdbc:mysql://localhost/infinity";
		Connection con = DriverManager.getConnection(url, "newuser", "password");
		System.out.println("Connection established......");
		//Retrieving the transaction isolation level
		int transactionIsoltionLevel = con.getTransactionIsolation();
		System.out.println("Transaction isolation level of the underlyingdatabase is: " + transactionIsoltionLevel);
	}
}

