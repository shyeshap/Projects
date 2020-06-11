package il.co.ilrd.chat_client;

import java.awt.BorderLayout;
import java.awt.Container;

import javax.swing.JFrame;


public class LoginFrame extends JFrame {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -582593631733082271L;
	LoginDetailPanel panel;
<<<<<<< HEAD
	ClientDemo client;
	
	public LoginFrame(String title, ClientDemo client) {
=======
	Client client;
	
	public LoginFrame(String title, Client client) {
>>>>>>> d47918d3f7a133ac41ab8c1ddd184079bc741119
		super(title);
		this.client = client;
		
		// set layout manager
		setLayout(new BorderLayout());
		
		// Create swing component
		panel = new LoginDetailPanel(client);
		
		// add swing components to content pane
		Container c = getContentPane();
		
		c.add(panel, BorderLayout.WEST);
	}
	
}
