package il.co.ilrd.chat_client;

import java.awt.BorderLayout;
import java.awt.Container;

import javax.swing.JFrame;



public class MainFrame extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = -582593631733082271L;
	MainDetailPanel panel;
<<<<<<< HEAD
	ClientDemo client;
	
	public MainFrame(String title, ClientDemo client, String name) {
=======
	Client client;
	
	public MainFrame(String title, Client client, String name) {
>>>>>>> d47918d3f7a133ac41ab8c1ddd184079bc741119
		super(title);
		this.client = client;
	
		// set layout manager
		setLayout(new BorderLayout());
		
		// Create swing component
		panel = new MainDetailPanel(client);
		panel.setBounds(0, 0, 100, 100);
		
		//client.panel = panel;
		// add swing components to content pane
		Container c = getContentPane();
		c.add(panel, BorderLayout.NORTH);
	}

}
	
