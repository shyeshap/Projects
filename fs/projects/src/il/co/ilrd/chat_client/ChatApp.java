package il.co.ilrd.chat_client;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;

public class ChatApp {
<<<<<<< HEAD
	public ChatApp(String titel) {
		
		ClientDemo client = new ClientDemo("localhost", 22222);
=======
	Client client;
	
	public ChatApp(String titel) {
		
		client = new Client("localhost", 22222);
>>>>>>> d47918d3f7a133ac41ab8c1ddd184079bc741119
		
		SwingUtilities.invokeLater(new Runnable() {
		
			public void run() {
				JFrame frame = new LoginFrame("Login to ChatApp", client);
				frame.setSize(300, 150);
				frame.setVisible(true);  
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			}
			
		});
<<<<<<< HEAD
		
	}
	
	public static void main(String[] args) {
=======
	}
	
	public static void main(String[] args) {
		
		
>>>>>>> d47918d3f7a133ac41ab8c1ddd184079bc741119
		new ChatApp("Login");
	}
}
